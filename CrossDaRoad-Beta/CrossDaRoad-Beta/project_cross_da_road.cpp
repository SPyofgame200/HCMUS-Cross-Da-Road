#include "hello_imgui/hello_imgui.h"
#include <imgui.h>
#include "cApp.h"
#include <thread>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>

// Function to allocate and redirect console
bool RedirectIOToConsole()
{
    // Allocate a console for this app
    if (!AllocConsole())
    {
        std::cerr << "Failed to allocate console." << std::endl;
        return false;
    }

    // Redirect STDOUT to the console
    FILE* fpOut;
    freopen_s(&fpOut, "CONOUT$", "w", stdout);
    if (fpOut == nullptr)
    {
        std::cerr << "Failed to redirect stdout." << std::endl;
        return false;
    }

    // Redirect STDERR to the console
    FILE* fpErr;
    freopen_s(&fpErr, "CONOUT$", "w", stderr);
    if (fpErr == nullptr)
    {
        std::cerr << "Failed to redirect stderr." << std::endl;
        return false;
    }

    // Redirect STDIN to the console
    FILE* fpIn;
    freopen_s(&fpIn, "CONIN$", "r", stdin);
    if (fpIn == nullptr)
    {
        std::cerr << "Failed to redirect stdin." << std::endl;
        return false;
    }

    // Sync C++ streams with C streams
    std::ios::sync_with_stdio(true);
    std::cin.tie(NULL);

    std::cout << "Console allocated and redirected successfully." << std::endl;
    return true;
}

// Function to enable Virtual Terminal Processing
bool EnableVirtualTerminalProcessing()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error: Unable to get standard output handle." << std::endl;
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        std::cerr << "Error: Unable to get console mode." << std::endl;
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        std::cerr << "Error: Unable to set console mode." << std::endl;
        return false;
    }

    return true;
}

// Function to get current working directory
std::string GetCurrentWorkingDirectory()
{
    DWORD length = GetCurrentDirectoryA(0, NULL);
    std::vector<char> buffer(length);
    GetCurrentDirectoryA(length, buffer.data());
    return std::string(buffer.data());
}

int main(int argc, char* argv[], char* envp[])
{
    // Allocate and redirect console for debugging
    if (!RedirectIOToConsole())
    {
        std::cerr << "Console allocation failed. Continuing without console." << std::endl;
    }
    else
    {
        // Enable Virtual Terminal Processing for ANSI colors
        if (!EnableVirtualTerminalProcessing())
        {
            std::cerr << "Failed to enable Virtual Terminal Processing." << std::endl;
        }
        else
        {
            std::cout << "\x1b[32mVirtual Terminal Processing enabled successfully.\x1b[0m" << std::endl;
        }

        // Print current working directory for debugging
        std::cout << "Current Working Directory: " << GetCurrentWorkingDirectory() << std::endl;
    }

    cApp app;

    // Initialize and construct the application
    if (app.Construct(app_const::SCREEN_WIDTH, app_const::SCREEN_HEIGHT, app_const::PIXEL_WIDTH, app_const::PIXEL_HEIGHT) == engine::SUCCESS)
    {
        if (app.Start() == engine::SUCCESS)
        {
            std::cout << "\x1b[34mStarting window message handling thread.\x1b[0m" << std::endl;

            // Start the window message handling in a separate thread
            auto windowThread = std::thread([&]() {
                app.window.HandleMessage();
                });

            std::cout << "\x1b[34mInitializing engine thread.\x1b[0m" << std::endl;

            // Initialize the engine thread
            app.InitEngineThread();

            // Setup HelloImGui runner parameters
            HelloImGui::RunnerParams runnerParams;
            runnerParams.appWindowParams.windowTitle = "Cross Da Road";
            runnerParams.appWindowParams.windowGeometry.size = { 1200, 800 };

            // Integrate HandleEngineEvent into the ImGui render loop
            runnerParams.callbacks.ShowGui = [&]() {
                // Handle game engine events
                if (!app.HandleEngineEvent()) {
                    std::cerr << "\x1b[31mEngine event handling returned false. Stopping ImGui.\x1b[0m" << std::endl;
                    PostQuitMessage(0); // Post a quit message to end the message loop
                }

                // Simulate delay
                Sleep(270);

                // Add your ImGui GUI code here
                ImGui::Text("Hello, Cross Da Road!");

                // Optional: Additional ImGui widgets for testing
                if (ImGui::Button("Test Button")) {
                    std::cout << "\x1b[35mTest Button Pressed!\x1b[0m" << std::endl;
                }

                // Example: Displaying colored text using ANSI codes
                std::cout << "\x1b[31m[DEBUG] This is red text.\x1b[0m" << std::endl;
                std::cout << "\x1b[32m[DEBUG] This is green text.\x1b[0m" << std::endl;
                std::cout << "\x1b[34m[DEBUG] This is blue text.\x1b[0m" << std::endl;
                };

            std::cout << "\x1b[34mRunning HelloImGui application.\x1b[0m" << std::endl;

            // Run the HelloImGui application
            HelloImGui::Run(runnerParams);

            std::cout << "\x1b[34mHelloImGui application has exited.\x1b[0m" << std::endl;

            // Cleanup
            app.ExitEngineThread();

            // Wait for the window thread to finish
            if (windowThread.joinable()) {
                windowThread.join();
                std::cout << "\x1b[34mWindow message handling thread has terminated.\x1b[0m" << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "\x1b[31mFailed to construct the application.\x1b[0m" << std::endl;
    }

    std::cout << "\x1b[32mApplication has exited successfully.\x1b[0m" << std::endl;

    // Optional: Free the console if no longer needed
    // FreeConsole();

    return 0;
}
