#ifndef C_PLAYER_RECORD_H
#define C_PLAYER_RECORD_H

#include <string>

class cPlayerRecord
{
private: // Player data 
	std::string sName;

public: // Constructors & Destructor
	cPlayerRecord();

public: // Initializer & Clean-up
	void Reset();

public: // Getters
	std::string GetName() const;

public: // Setters
	void SetName(const std::string& sName);

};

#endif // C_PLAYER_RECORD_H

