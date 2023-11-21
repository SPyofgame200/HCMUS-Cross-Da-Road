#ifndef U_MESSAGE_MANAGER
#define U_MESSAGE_MANAGER

#include <iostream>
#include <sstream>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <future>

namespace text {
    // Reset
    constexpr const char* RESET = "\033[0m";
    // Text color
    constexpr const char* BLACK = "\033[30m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* YELLOW = "\033[33m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN = "\033[36m";
    constexpr const char* WHITE = "\033[37m";
    // Bright text color
    constexpr const char* BRIGHT_BLACK = "\033[1;30m";
    constexpr const char* BRIGHT_RED = "\033[1;31m";
    constexpr const char* BRIGHT_GREEN = "\033[1;32m";
    constexpr const char* BRIGHT_YELLOW = "\033[1;33m";
    constexpr const char* BRIGHT_BLUE = "\033[1;34m";
    constexpr const char* BRIGHT_MAGENTA = "\033[1;35m";
    constexpr const char* BRIGHT_CYAN = "\033[1;36m";
    constexpr const char* BRIGHT_WHITE = "\033[1;37m";
    // Additional text colors
    constexpr const char* ORANGE = "\033[38;5;208m";
    constexpr const char* PINK = "\033[38;5;200m";
    constexpr const char* PURPLE = "\033[38;5;171m";
    constexpr const char* LIME = "\033[38;5;154m";
    constexpr const char* TEAL = "\033[38;5;30m";
    constexpr const char* OLIVE = "\033[38;5;58m";
    constexpr const char* BROWN = "\033[38;5;130m";
    constexpr const char* GRAY = "\033[90m";
}

namespace background {
    // Reset
    constexpr const char* RESET = "\033[49m";
    // Background color
    constexpr const char* BLACK = "\033[40m";
    constexpr const char* RED = "\033[41m";
    constexpr const char* GREEN = "\033[42m";
    constexpr const char* YELLOW = "\033[43m";
    constexpr const char* BLUE = "\033[44m";
    constexpr const char* MAGENTA = "\033[45m";
    constexpr const char* CYAN = "\033[46m";
    constexpr const char* WHITE = "\033[47m";
    // Bright blackground colors
    constexpr const char* BRIGHT_BLACK = "\033[1;40m";
    constexpr const char* BRIGHT_RED = "\033[1;41m";
    constexpr const char* BRIGHT_GREEN = "\033[1;42m";
    constexpr const char* BRIGHT_YELLOW = "\033[1;43m";
    constexpr const char* BRIGHT_BLUE = "\033[1;44m";
    constexpr const char* BRIGHT_MAGENTA = "\033[1;45m";
    constexpr const char* BRIGHT_CYAN = "\033[1;46m";
    constexpr const char* BRIGHT_WHITE = "\033[1;47m";
    // Additional background colors
    constexpr const char* ORANGE = "\033[48;5;208m";
    constexpr const char* PINK = "\033[48;5;200m";
    constexpr const char* PURPLE = "\033[48;5;171m";
    constexpr const char* LIME = "\033[48;5;154m";
    constexpr const char* TEAL = "\033[48;5;30m";
    constexpr const char* OLIVE = "\033[48;5;58m";
    constexpr const char* BROWN = "\033[48;5;130m";
    constexpr const char* GRAY = "\033[100m";
}

enum MessageSeverity
{
    LOG = 0,
    WARN = 1,
    ERROR = 2,
    SEVERE = 3,
    CUSTOMS = 4,
};

class MessageManager {
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
    const int tokenBaseInterval = 100;
    const int tokenIntervalsMultiplier[4] = { 5, 10, 20, 40 }; // based on the severity

private:
    clock_t CurrentTime()
    {
        return std::chrono::steady_clock::now();
    }

    sysclock_t CurrentSystime()
    {
        return std::chrono::system_clock::now();
    }

private:
    MessageManager() 
    : lastMessageTimer{ CurrentTime(), CurrentTime(), CurrentTime(), CurrentTime() }
    , originTimer(CurrentTime()), originSystimer(CurrentSystime())
    {
    }

public:
    static MessageManager& GetInstance() 
    {
        static MessageManager instance;
        return instance;
    }

public:
    void Log(MessageSeverity eSeverity, const std::string& sMessage, const std::string& sFunctionName = "", const std::string sFilePath = "") const 
    {
        std::async(std::launch::async, &MessageManager::LogThread, this, sFilePath, sFunctionName, sMessage, eSeverity);
    }

public:
    bool TryAcquireToken(MessageSeverity eSeverity) const 
    {
        std::lock_guard<std::mutex> lock(tokenMutex);
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMessageTimer[static_cast<int>(eSeverity)]);

        if (elapsed.count() >= (tokenBaseInterval * tokenIntervalsMultiplier[static_cast<int>(eSeverity)])) {
            lastMessageTimer[static_cast<int>(eSeverity)] = now;
            return true;
        }

        return false;
    }

private:
    void LogRealTime() const {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto elapsedSinceStart = duration_cast<milliseconds>(now - originSystimer);

        auto minutes_part = duration_cast<minutes>(elapsedSinceStart);
        auto seconds_part = duration_cast<seconds>(elapsedSinceStart - minutes_part);
        auto milliseconds_part = duration_cast<milliseconds>(elapsedSinceStart - minutes_part - seconds_part);

        auto time = system_clock::to_time_t(now);
        tm tm_time;
        localtime_s(&tm_time, &time);

        std::cerr << text::BRIGHT_BLUE << "["
            << std::put_time(&tm_time, "%d/%m/%y at %H:%M:%S")
            << "." << std::setw(6) << std::setfill('0') << milliseconds_part.count()
        << "] ";
    }

    void LogTimestamp() const
    {
        using namespace std::chrono;

        clock_t now = steady_clock::now();
        milliseconds elapsedSinceStart = duration_cast<milliseconds>(now - originTimer);

        minutes minutes_part = duration_cast<minutes>(elapsedSinceStart);
        seconds seconds_part = duration_cast<seconds>(elapsedSinceStart - duration_cast<milliseconds>(minutes_part));
        milliseconds milisec_part = elapsedSinceStart - duration_cast<milliseconds>(minutes_part) - duration_cast<milliseconds>(seconds_part);

        std::cerr << text::CYAN << "["
            << std::setw(2) << std::setfill('0') << minutes_part.count() << ":"  // minutes
            << std::setw(2) << std::setfill('0') << seconds_part.count() << "."  // seconds
            << std::setw(3) << std::setfill('0') << milisec_part.count() // milliseconds
        << "] ";
    }

    void LogSeverity(MessageSeverity eSeverity, bool bReset = false) const
    {
        switch (eSeverity)
        {
        case LOG:
            std::cerr << text::GRAY << "[LOG]";
            break;
        case WARN:
            std::cerr << text::YELLOW << "[WARN]";
            break;
        case ERROR:
            std::cerr << text::ORANGE << "[ERROR]";
            break;
        case SEVERE:
            std::cerr << text::RED << "[SEVERE]";
            break;
        default:
            std::cerr << text::BROWN << "[CUSTOM]";
            break;
        }
        std::cerr << " ";
        if (bReset) {
            std::cerr << text::RESET << background::RESET << std::endl;
        }
    }

    void LogThread(const std::string& sFilePath, const std::string& sFunctionName, const std::string& sMessage, MessageSeverity eSeverity) const {
        std::lock_guard<std::mutex> lock(logMutex);
        if (eSeverity == MessageSeverity::SEVERE) {
            LogRealTime();
        }
        LogTimestamp();
        LogSeverity(eSeverity);
        if (sFilePath.size()) {
            std::cerr << text::PURPLE << sFilePath << " -> ";
        }
        if (sFunctionName.size()) {
            std::cerr << text::WHITE << sFunctionName << "(): ";
        }
        std::cerr << text::GRAY << sMessage << text::RESET << std::endl;
    }
};

// Logging macro
#define LOG_MESSAGE(message) \
    do { \
        if (MessageManager::GetInstance().TryAcquireToken(MessageSeverity::LOG)) { \
            std::ostringstream logStream; \
            logStream << message; \
            MessageManager::GetInstance().Log(MessageSeverity::LOG, logStream.str()); \
        } \
    } while(0)

#define WARN_MESSAGE(message) \
    do { \
        if (MessageManager::GetInstance().TryAcquireToken(MessageSeverity::WARN)) { \
            std::ostringstream logStream; \
            logStream << message; \
            MessageManager::GetInstance().Log(MessageSeverity::WARN, logStream.str(), __func__); \
        } \
    } while(0)

#define ERROR_MESSAGE(message) \
    do { \
        if (MessageManager::GetInstance().TryAcquireToken(MessageSeverity::ERROR)) { \
            std::ostringstream logStream; \
            logStream << message; \
            MessageManager::GetInstance().Log(MessageSeverity::ERROR, logStream.str(), __func__, __FILE__); \
        } \
    } while(0)

#define SEVERE_MESSAGE(message) \
    do { \
        if (MessageManager::GetInstance().TryAcquireToken(MessageSeverity::SEVERE)) { \
            std::ostringstream logStream; \
            logStream << message; \
            MessageManager::GetInstance().Log(MessageSeverity::SEVERE, logStream.str(), __func__, __FILE__); \
        } \
    } while(0)

#endif // U_MESSAGE_MANAGER

/*
    TODO

    for players, by log level 1 -> 5

    NOTIFY_MESSAGE(message, logfile = default): The app is running fine, just output certain actions
    - color: Brown
    - format: [MM:SS] message
    EVENT_MESSAGE(function_name, message, logfile = default): The app is running fine, just output the current event
    - color: Cyan
    - format: [MM:SS.s] function_name(): message
    WARN_MESSAGE(function_name, message, logfile = default): The app still runs with unwanted side effects
    - color: Yellow
    - format: [MM:SS.ss] function_name(parameters): message
    ERROR_MESSAGE(file_path, function_name, message, logfile = default): The app can not run with current state
    - color: Orange
    - format: [MM:SS.ssss] ./file_path/file_name.file_extension::function_name(parameters): message
    SEVERE_MESSAGE(file_path, function_name, message, this, logfile = default): Something shouldnt happen just happened
    - color: Red
    - format: [HH:MM:SS.ssssss] ./file_path/file_name.file_extension::function_name(parameters): message \n std::cerr<<*this<<std::endl;

    for developers

    LOG_MESSAGE(message): I want to output a simple message
    - output the message
    - color: Lime
    - format: same as NOTIFY_MESSAGE
    INFO_MESSAGE(function_name, message): I want to get the informative message
    - output current function_name
    - output the messages with function parameters
    - color: Blue
    - format: same as WARN_MESSAGE
    TRACE_MESSAGE(file_path, function_name, message, this): I want to debug with details states
    - output current filepath with the namespace and function_name
    - output the messages with class data
    - color: Purple
    - format: same as SEVERE_MESSAGE
*/