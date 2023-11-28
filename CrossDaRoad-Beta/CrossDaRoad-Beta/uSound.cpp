/**
 * @file uSound.cpp
 *
 * @brief Contains sound functions
 *
 * This file implements sound functions.
**/

#include "uSound.h"

#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <iostream>

//=================================================================================================
// Include new header files here

//=================================================================================================

/// @brief Namespace for application sound
namespace app_sound
{
    /// @brief Stops the music with the given alias name
    /// @param alias The alias name of the music thread
    /// @return True if the music thread is stopped successfully, false otherwise
    bool StopMusic(const std::string& alias)
    {
        const std::string command = "stop " + alias;
        if (mciSendStringA(command.c_str(), nullptr, 0, nullptr) != 0) {
            std::cerr << "Failed to stop the music." << std::endl;
            return false;
        }
        return true;
    }

    /// @brief Plays a custom sound with the given alias name and audio
    /// @param audioFilePath The path to the audio file
    /// @param alias The alias name of the music thread
    /// @return True if the music thread is played successfully, false otherwise
    bool PlayCustomSound(const std::string& audioFilePath, const std::string& alias)
    {
        CloseMusicThread(alias);
        const std::string command = "open \"" + audioFilePath + "\" type waveaudio alias " + alias;
        if (mciSendStringA(command.c_str(), nullptr, 0, nullptr) != 0) {
            std::cerr << "Can not open music file (" << audioFilePath << ")" << std::endl;
            return false;
        }
        const std::string playCommand = "play " + alias;
        mciSendStringA(playCommand.c_str(), nullptr, 0, nullptr);
        return true;
    }

    /// @brief Plays a WAV file with the given alias name and audio
    /// @param audioFilePath Path to the audio file
    /// @param alias Alias name of the music thread
    /// @return Always returns true by default
    bool PlayWAV(const std::string& audioFilePath, const std::string& alias)
    {
        // Lock the mutex to ensure only one thread can enter at a time
        PlayCustomSound(audioFilePath);
        return true;
    }

    /// @brief Plays a music with the given alias name and audio
    /// @param musicName Name of the music file
    /// @param alias Alias name of the music thread
    /// @return Always returns true by default
    bool PlayMusic(const std::string& musicName, const std::string& alias)
    {
        const std::string audioFilePath = "data/musics/" + musicName + ".wav";
        PlayWAV(audioFilePath);
        return true;
    }

    /// @brief Closes the music thread with the given alias name
    /// @param alias Alias name of the music thread
    /// @return Always returns true by default
    bool CloseMusicThread(const std::string& alias)
    {
        const std::string command = "close " + alias;
        mciSendStringA(command.c_str(), nullptr, 0, nullptr);
        return true;
    }

    /// @brief Stops the music with the default alias name
    /// @return True if the music thread is stopped successfully, false otherwise
    bool StopMusic()
    {
        return StopMusic(ALIAS);
    }

    /// @brief Plays a custom sound with the default alias name and audio
    /// @param audioFilePath Path to the audio file
    /// @return True if the music thread is played successfully, false otherwise
    bool PlayCustomSound(const std::string& audioFilePath)
    {
        return PlayCustomSound(audioFilePath, ALIAS);
    }

    /// @brief Plays a WAV file with the default alias name and audio
    /// @param audioFilePath Path to the audio file
    /// @return Always returns true by default
    bool PlayWAV(const std::string& audioFilePath)
    {
        return PlayWAV(audioFilePath, ALIAS);
    }

    /// @brief Plays a music with the default alias name and specified music 
    /// @param musicName Name of the music file
    /// @return Always returns true by default
    bool PlayMusic(const std::string& musicName)
    {
        return PlayMusic(musicName, ALIAS);
    }

    /// @brief Closes the music thread with the default alias name
    /// @return Always returns true by default
    bool CloseMusicThread()
    {
        return CloseMusicThread(ALIAS);
    }

    /// @brief Checks if the music is playing
    /// @return True if the music is playing, false otherwise
    bool bMusicPlaying()
    {
        MCI_STATUS_PARMS statusParams;
        statusParams.dwItem = MCI_STATUS_MODE;
        mciSendCommand(MCI_ALL_DEVICE_ID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, reinterpret_cast<DWORD_PTR>(&statusParams));

        if (statusParams.dwReturn == MCI_MODE_PLAY) {
            return true;
        }
        else {
            return false;
        }
    }
} // namespace app_sound

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// END OF FILE ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////