#ifndef U_MESSAGE_MANAGER
#define U_MESSAGE_MANAGER

#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <iomanip>

class MessageManager {
public:
    static MessageManager& GetInstance() {
        static MessageManager instance;
        return instance;
    }

    void Log(const std::string& functionName, const std::string& message) const {
        if (TryAcquireToken()) {
            auto now = std::chrono::steady_clock::now();
            auto elapsedSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(now - programStartTime);

            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsedSinceStart);
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsedSinceStart - minutes);
            auto milliseconds = elapsedSinceStart - minutes - seconds;

            std::cerr << "[" << std::setw(2) << std::setfill('0') << minutes.count() << ":"
                << std::setw(2) << std::setfill('0') << seconds.count() << "."
                << std::setw(3) << milliseconds.count() << "] ";
            std::cerr << functionName << "(): " << message << std::endl;
        }
    }

private:
    MessageManager() : lastMessageTime(std::chrono::steady_clock::now()), programStartTime(std::chrono::steady_clock::now()) {}

    bool TryAcquireToken() const {
        std::lock_guard<std::mutex> lock(tokenMutex);
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMessageTime);

        if (elapsed.count() >= tokenInterval) {
            lastMessageTime = now;
            return true;
        }

        return false;
    }

    mutable std::mutex tokenMutex;
    mutable std::chrono::steady_clock::time_point lastMessageTime;
    const std::chrono::steady_clock::time_point programStartTime;
    const int tokenInterval = 100; // 100 milliseconds interval between tokens
};

// Logging macro
#define LOG_ERROR(message) \
    do { \
        std::ostringstream logStream; \
        logStream << message; \
        MessageManager::GetInstance().Log(__func__, logStream.str()); \
    } while(0)

#endif // U_MESSAGE_MANAGER
