#ifndef C_PLAYER_RECORD_H
#define C_PLAYER_RECORD_H

#include <string>

class cPlayerRecord
{
private: // might be moved into cPlayerCustom
	int frame6_id_animation_safe;

private: // Player data 
	std::string sName;

public: // Constructors & Destructor
	cPlayerRecord();

public: // Initializer & Clean-up
	void Reset();

public: // Utilities (might be moved into cPlayerCustom)
	int GetSafeAnimationID() const;

public: // Getters
	std::string GetPlayerName() const;

public: // Setters
	void SetPlayerName(const std::string& sName);

};

#endif // C_PLAYER_RECORD_H

