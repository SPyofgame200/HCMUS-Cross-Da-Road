#ifndef U_MESSAGE_MANAGER
#define U_MESSAGE_MANAGER

#include <iostream>
#include <sstream>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <future>
#include <fstream>
#include "uConsoleColor.h"

enum MessageSeverity
{
    LOG = 0,
    WARN = 1,
    ERROR = 2,
    SEVERE = 3,
    CUSTOMS = 4,
};

class cMessageManager {
private: /// Timer controls
    using clock_t = std::chrono::steady_clock::time_point;
    using sysclock_t = std::chrono::system_clock::time_point;
    mutable clock_t lastMessageTimer[4];  // Array for each severity level timer
    const clock_t originTimer;
    const sysclock_t originSystimer;

private: /// Avoid data-race between threads
    mutable std::mutex tokenMutex;
    mutable std::mutex logMutex;

private: /// User customization
    const int nIntervalMilisecond = 100;
    const int nIntervalMultiplier[4] = { 2, 4, 8, 16 }; // based on the severity

private:
    clock_t CurrentTime()
    {
        return std::chrono::steady_clock::now();
    }

    sysclock_t CurrentSystime()
    {
        return std::chrono::system_clock::now();
    }

private: /// Constructor & Destructor
    cMessageManager() 
    : lastMessageTimer{ CurrentTime(), CurrentTime(), CurrentTime(), CurrentTime() }
    , originTimer(CurrentTime()), originSystimer(CurrentSystime())
    {
        // ...
    }
    ~cMessageManager()
    {
        // ...
    }

public: /// Singleton
    static cMessageManager& GetInstance() 
    {
        static cMessageManager instance;
        return instance;
    }

public: /// Validator
    bool TryAcquireToken(MessageSeverity eSeverity) const
    {
        std::lock_guard<std::mutex> lock(tokenMutex);
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMessageTimer[static_cast<int>(eSeverity)]);

        if (elapsed.count() >= static_cast<int64_t>(nIntervalMilisecond) * nIntervalMultiplier[static_cast<int>(eSeverity)]) {
            lastMessageTimer[static_cast<int>(eSeverity)] = now;
            return true;
        }

        return false;
    }

public: // Loggers
    void Log(MessageSeverity eSeverity, const std::string& sMessage, const std::string& sFunctionName = "", const std::string sFilePath = "", int nLineIndex = 0) const
    {
        auto future = std::async(std::launch::async, &cMessageManager::LogThread, this, eSeverity, sMessage, sFunctionName, sFilePath, nLineIndex);
        future.wait();
    }

public: // Getters
    std::string GetMessage(MessageSeverity eSeverity, const std::string& sMessage, const std::string& sFunctionName = "", const std::string sFilePath = "", int nLineIndex = 0) const
    {
        std::ostringstream logStream;
        if (eSeverity == MessageSeverity::SEVERE) {
            LogRealTime(logStream);
        }
        LogTimestamp(logStream);
        LogSeverity(logStream, eSeverity);
        if (sFilePath.size()) {
            logStream << text::PURPLE << "\"" << sFilePath << "\" ";
        }
        if (nLineIndex) {
            logStream << text::BRIGHT_BLUE << "Line [" << nLineIndex << "] ";
        }
        if (sFunctionName.size()) {
            logStream << text::WHITE << sFunctionName << "(): ";
        }
        logStream << text::GRAY << sMessage << text::RESET;
        return logStream.str();
    }

private: // Log handler
    void LogThread(MessageSeverity eSeverity, const std::string& sMessage, const std::string& sFunctionName = "", const std::string sFilePath = "", int nLineIndex = 0) const {
        std::lock_guard<std::mutex> lock(logMutex);
        std::cerr << GetMessage(eSeverity, sMessage, sFunctionName, sFilePath, nLineIndex) << std::endl;
    }
    void LogRealTime(std::ostream& logStream) const {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto elapsedSinceStart = duration_cast<milliseconds>(now - originSystimer);

        auto minutes_part = duration_cast<minutes>(elapsedSinceStart);
        auto seconds_part = duration_cast<seconds>(elapsedSinceStart - minutes_part);
        auto milliseconds_part = duration_cast<milliseconds>(elapsedSinceStart - minutes_part - seconds_part);

        auto time = system_clock::to_time_t(now);
        tm tm_time;
        localtime_s(&tm_time, &time);

        logStream << text::BRIGHT_BLUE << "["
            << std::put_time(&tm_time, "%d/%m/%y at %H:%M:%S")
            << "." << std::setw(6) << std::setfill('0') << milliseconds_part.count()
            << "] ";
    }

    void LogTimestamp(std::ostream& logStream) const
    {
        using namespace std::chrono;

        clock_t now = steady_clock::now();
        milliseconds elapsedSinceStart = duration_cast<milliseconds>(now - originTimer);

        minutes minutes_part = duration_cast<minutes>(elapsedSinceStart);
        seconds seconds_part = duration_cast<seconds>(elapsedSinceStart - duration_cast<milliseconds>(minutes_part));
        milliseconds milisec_part = elapsedSinceStart - duration_cast<milliseconds>(minutes_part) - duration_cast<milliseconds>(seconds_part);

        logStream << text::CYAN << "["
            << std::setw(2) << std::setfill('0') << minutes_part.count() << ":"  // minutes
            << std::setw(2) << std::setfill('0') << seconds_part.count() << "."  // seconds
            << std::setw(3) << std::setfill('0') << milisec_part.count() // milliseconds
            << "] ";
    }

    void LogSeverity(std::ostream& logStream, MessageSeverity eSeverity, bool bReset = false) const
    {
        switch (eSeverity)
        {
        case LOG:
            logStream << text::GRAY << "[LOG]";
            break;
        case WARN:
            logStream << text::YELLOW << "[WARN]";
            break;
        case ERROR:
            logStream << text::ORANGE << "[ERROR]";
            break;
        case SEVERE:
            logStream << text::RED << "[SEVERE]";
            break;
        default:
            logStream << text::BROWN << "[CUSTOM]";
            break;
        }
        logStream << " ";
        if (bReset) {
            logStream << text::RESET << background::RESET << std::endl;
        }
    }
};


#include <tuple>
template <typename... Args>
constexpr std::size_t CountArguments(Args...) {
    return sizeof...(Args);
}

#define PRINT_ARG_COUNT(...) \
    do { \
        constexpr std::size_t numArgs = CountArguments(__VA_ARGS__); \
        std::cerr << "[" << numArgs << " args ]" << std::endl; \
    } while(0)

// Logging macro
#define LOG_MESSAGE(message) \
    do { \
        if (cMessageManager::GetInstance().TryAcquireToken(MessageSeverity::LOG)) { \
            std::ostringstream logStream; \
            logStream << message; \
            cMessageManager::GetInstance().Log(MessageSeverity::LOG, logStream.str()); \
        } \
    } while(0)

#define WARN_MESSAGE(message) \
    do { \
        if (cMessageManager::GetInstance().TryAcquireToken(MessageSeverity::WARN)) { \
            std::ostringstream logStream; \
            logStream << message; \
            cMessageManager::GetInstance().Log(MessageSeverity::WARN, logStream.str(), __func__); \
        } \
    } while(0)

#define ERROR_MESSAGE(message) \
    do { \
        if (cMessageManager::GetInstance().TryAcquireToken(MessageSeverity::ERROR)) { \
            std::ostringstream logStream; \
            logStream << message; \
            cMessageManager::GetInstance().Log(MessageSeverity::ERROR, logStream.str(), __func__, __FILE__); \
        } \
    } while(0)

#define SEVERE_MESSAGE(message) \
    do { \
        if (cMessageManager::GetInstance().TryAcquireToken(MessageSeverity::SEVERE)) { \
            std::ostringstream logStream; \
            logStream << message; \
            cMessageManager::GetInstance().Log(MessageSeverity::SEVERE, logStream.str(), __func__, __FILE__, __LINE__); \
        } \
    } while(0)

#endif // U_MESSAGE_MANAGER
