#include "cPlayerRecord.h"

cPlayerRecord::cPlayerRecord()
{
	Reset();
}

void cPlayerRecord::Reset()
{
	sName = "";
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