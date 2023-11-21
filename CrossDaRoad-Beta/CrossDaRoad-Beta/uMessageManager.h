#ifndef U_MESSAGE_MANAGER
#define U_MESSAGE_MANAGER

#include <iostream>
#include <sstream>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <future>

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
        std::cerr << functionName << "(): " << message << std::endl;
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
