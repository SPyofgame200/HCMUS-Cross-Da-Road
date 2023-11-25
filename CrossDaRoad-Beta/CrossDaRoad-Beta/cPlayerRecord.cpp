#include "cPlayerRecord.h"

cPlayerRecord::cPlayerRecord()
{
	Reset();
}

void cPlayerRecord::Reset()
{
	frame6_id_animation_safe = 5;
	sName = "";
}

int cPlayerRecord::GetSafeAnimationID() const
{
	return frame6_id_animation_safe;
}

/// @brief Getter for player name
std::string cPlayerRecord::GetPlayerName() const
{
	return sName;
}

/// @brief Setter for player name
/// @param Name Name of player
void cPlayerRecord::SetPlayerName(const std::string& Name)
{
	this->sName = Name;
}