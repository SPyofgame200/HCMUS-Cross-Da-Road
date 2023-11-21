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
}

namespace background {
    // Background color
    constexpr const char* BLACK = "\033[40m";
    constexpr const char* RED = "\033[41m";
    constexpr const char* GREEN = "\033[42m";
    constexpr const char* YELLOW = "\033[43m";
    constexpr const char* BLUE = "\033[44m";
    constexpr const char* MAGENTA = "\033[45m";
    constexpr const char* CYAN = "\033[46m";
    constexpr const char* WHITE = "\033[47m";
    // Reset background color
    constexpr const char* RESET = "\033[49m";

    constexpr const char* BRIGHT_BLACK = "\033[1;40m";
    constexpr const char* BRIGHT_RED = "\033[1;41m";
    constexpr const char* BRIGHT_GREEN = "\033[1;42m";
    constexpr const char* BRIGHT_YELLOW = "\033[1;43m";
    constexpr const char* BRIGHT_BLUE = "\033[1;44m";
    constexpr const char* BRIGHT_MAGENTA = "\033[1;45m";
    constexpr const char* BRIGHT_CYAN = "\033[1;46m";
    constexpr const char* BRIGHT_WHITE = "\033[1;47m";
}

class MessageManager {
private: /// Timer
    using clock_t = std::chrono::steady_clock::time_point;
    mutable clock_t lastMessageTimer;
    const clock_t origin;

private: /// Prevent Data Race
    mutable std::mutex tokenMutex;
    mutable std::mutex logMutex;

private: /// Message controllers
    const int tokenInterval = 500; // 100 milliseconds interval between tokens

private:
    clock_t CurrentTime()
    {
        return std::chrono::steady_clock::now();
    }

private: /// Constructor
    MessageManager() : lastMessageTimer(CurrentTime()), origin(CurrentTime()) {}

public: // Singleton
    static MessageManager& GetInstance() {
        static MessageManager instance;
        return instance;
    }

public: // Loggers
    void Log(const std::string& functionName, const std::string& message) const {
        std::async(std::launch::async, &MessageManager::LogThread, this, functionName, message);
    }

public: // Validators
    bool TryAcquireToken() const {
        std::lock_guard<std::mutex> lock(tokenMutex);
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMessageTimer);

        if (elapsed.count() >= tokenInterval) {
            lastMessageTimer = now;
            return true;
        }

        return false;
    }

private: /// Log Internality
    void LogTimestamp() const {
        using namespace std::chrono;

        clock_t now = steady_clock::now();
        milliseconds elapsedSinceStart = duration_cast<milliseconds>(now - origin);

        minutes minutes_part = duration_cast<minutes>(elapsedSinceStart);
        seconds seconds_part = duration_cast<seconds>(elapsedSinceStart - duration_cast<milliseconds>(minutes_part));
        milliseconds milisec_part = elapsedSinceStart - duration_cast<milliseconds>(minutes_part) - duration_cast<milliseconds>(seconds_part);

        std::cerr << "[" 
            << std::setw(2) << std::setfill('0') << minutes_part.count() << ":" // minutes
            << std::setw(2) << std::setfill('0') << seconds_part.count() << "." // seconds
            << std::setw(3) << std::setfill('0') << milisec_part.count()        // miliseconds
        << "] ";
    }

    void LogThread(const std::string& functionName, const std::string& message) const {
        std::lock_guard<std::mutex> lock(logMutex);
        LogTimestamp();  // Log timestamp separately
        std::cerr << text::RED << functionName << "(): " << message << text::RESET << std::endl;
    }
};

// Logging macro
#define LOG_ERROR(message) \
    do { \
        if (MessageManager::GetInstance().TryAcquireToken()) { \
            std::ostringstream logStream; \
            logStream << message; \
            MessageManager::GetInstance().Log(__func__, logStream.str()); \
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