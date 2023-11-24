#ifndef C_MESSAGE_MANAGER
#define C_MESSAGE_MANAGER

#include <iostream>
#include <sstream>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <future>

#include "uConsoleColor.h"

enum MessageSeverity
{
    LOG_MESSAGE = 0,
    WARN_MESSAGE = 1,
    ERROR_MESSAGE = 2,
    SEVERE_MESSAGE = 3,
    SPECIAL_MESSAGE = 4,
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
        LogConsoleColor();
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
	    const auto now = std::chrono::steady_clock::now();
	    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMessageTimer[static_cast<int>(eSeverity)]);

        if (elapsed.count() >= static_cast<int64_t>(nIntervalMilisecond) * nIntervalMultiplier[static_cast<int>(eSeverity)]) {
            lastMessageTimer[static_cast<int>(eSeverity)] = now;
            return true;
        }

        return false;
    }

public: // Loggers
    void Log(MessageSeverity eSeverity, const std::string& sMessage, const std::string& sFunctionName = "", const std::string& sFilePath = "", int nLineIndex = 0) const
    {
        auto future = std::async(std::launch::async, &cMessageManager::LogThread, this, eSeverity, sMessage, sFunctionName, sFilePath, nLineIndex);
    }

    void LogConsoleColor()
    {
        console::ShowConsoleColor();
    }

public: // Getters
    std::string GetMessage(MessageSeverity eSeverity, const std::string& sMessage, const std::string& sFunctionName = "", const std::string& sFilePath = "", int nLineIndex = 0) const
    {
        std::ostringstream logStream;
        if (eSeverity == MessageSeverity::SEVERE_MESSAGE) {
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
    void LogThread(MessageSeverity eSeverity, const std::string& sMessage, const std::string& sFunctionName = "", const std::string& sFilePath = "", int nLineIndex = 0) const {
        std::lock_guard<std::mutex> lock(logMutex);
        std::cerr << GetMessage(eSeverity, sMessage, sFunctionName, sFilePath, nLineIndex) << std::endl;
    }
    void LogRealTime(std::ostream& logStream) const {
        using namespace std::chrono;

        const auto now = system_clock::now();
        const auto elapsedSinceStart = duration_cast<milliseconds>(now - originSystimer);

        const auto minutes_part = duration_cast<minutes>(elapsedSinceStart);
        const auto seconds_part = duration_cast<seconds>(elapsedSinceStart - minutes_part);
        const auto milliseconds_part = duration_cast<milliseconds>(elapsedSinceStart - minutes_part - seconds_part);

        const auto time = system_clock::to_time_t(now);
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

        const clock_t now = steady_clock::now();
        const milliseconds elapsedSinceStart = duration_cast<milliseconds>(now - originTimer);

        const minutes minutes_part = duration_cast<minutes>(elapsedSinceStart);
        const seconds seconds_part = duration_cast<seconds>(elapsedSinceStart - duration_cast<milliseconds>(minutes_part));
        const milliseconds milisec_part = elapsedSinceStart - duration_cast<milliseconds>(minutes_part) - duration_cast<milliseconds>(seconds_part);

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
        case LOG_MESSAGE:
            logStream << text::GRAY << "[LOG]";
            break;
        case WARN_MESSAGE:
            logStream << text::YELLOW << "[WARN]";
            break;
        case ERROR_MESSAGE:
            logStream << text::ORANGE << "[ERROR]";
            break;
        case SEVERE_MESSAGE:
            logStream << text::RED << "[SEVERE]";
            break;
        default:
            logStream << text::BROWN << "[SPECIAL]";
            break;
        }
        logStream << " ";
        if (bReset) {
            logStream << text::RESET << background::RESET << std::endl;
        }
    }
};

// Utilities macros
#include <tuple>
template <typename... Args>
constexpr std::size_t CountArguments(Args...) {
    return sizeof...(Args);
}

#define LOG_ARG_COUNT(...) \
    do { \
        constexpr std::size_t numArgs = CountArguments(__VA_ARGS__); \
        std::cerr << "[" << numArgs << " args ]" << std::endl; \
    } while(0)

#define LOG_COLORS() \
    do { \
       cMessageManager::GetInstance().LogConsoleColor(); \
    } while(0)


// Logging macro
#define LOG_MESSAGE(message) \
    do { \
        if (cMessageManager::GetInstance().TryAcquireToken(MessageSeverity::LOG_MESSAGE)) { \
            std::ostringstream logStream; \
            logStream << message; \
            cMessageManager::GetInstance().Log(MessageSeverity::LOG_MESSAGE, logStream.str()); \
        } \
    } while(0)

#define WARN_MESSAGE(message) \
    do { \
        if (cMessageManager::GetInstance().TryAcquireToken(MessageSeverity::WARN_MESSAGE)) { \
            std::ostringstream logStream; \
            logStream << message; \
            cMessageManager::GetInstance().Log(MessageSeverity::WARN_MESSAGE, logStream.str(), __func__); \
        } \
    } while(0)

#define ERROR_MESSAGE(message) \
    do { \
        if (cMessageManager::GetInstance().TryAcquireToken(MessageSeverity::ERROR_MESSAGE)) { \
            std::ostringstream logStream; \
            logStream << message; \
            cMessageManager::GetInstance().Log(MessageSeverity::ERROR_MESSAGE, logStream.str(), __func__, __FILE__); \
        } \
    } while(0)

#define SEVERE_MESSAGE(message) \
    do { \
        if (cMessageManager::GetInstance().TryAcquireToken(MessageSeverity::SEVERE_MESSAGE)) { \
            std::ostringstream logStream; \
            logStream << message; \
            cMessageManager::GetInstance().Log(MessageSeverity::SEVERE_MESSAGE, logStream.str(), __func__, __FILE__, __LINE__); \
        } \
    } while(0)

#endif // C_MESSAGE_MANAGER
