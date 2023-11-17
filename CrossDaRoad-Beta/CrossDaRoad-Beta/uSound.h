/**
 * @file uSound.h
 *
 * @brief Contains sound functions
 *
 * This file contains sound function prototypes.
 **/

#ifndef U_SOUND_H
#define U_SOUND_H

#include <string>

 /// @brief Namespace for sound functions and constants
namespace app_sound
{
	const std::string ALIAS = "SOUND"; ///< Alias for sound thread

	bool StopMusic(const std::string& alias);
	bool PlayCustomSound(const std::string& audioFilePath, const std::string& alias);
	bool PlayWAV(const std::string& audioFilePath, const std::string& alias);
	bool PlayMusic(const std::string& musicName, const std::string& alias);
	bool CloseMusicThread(const std::string& alias);

	bool StopMusic();
	bool PlayCustomSound(const std::string& audioFilePath);
	bool PlayWAV(const std::string& audioFilePath);
	bool PlayMusic(const std::string& musicName);
	bool CloseMusicThread();
	bool bMusicPlaying();
};

#endif // U_SOUND_H