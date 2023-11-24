#ifndef H_PLAYER_PHYSICAL_H
#define H_PLAYER_PHYSICAL_H

// forward declaration
class hPlayer;

class hPlayerPhysical
{
private: // Dependency
	hPlayer* ptrPlayer;

public: // Constructors & Destructor
	hPlayerPhysical();
	hPlayerPhysical(hPlayer* ptrPlayer);
	~hPlayerPhysical();

public: // Initializer & Clean-up
	bool SetupTarget(hPlayer* ptrPlayer);

};

#endif H_PLAYER_PHYSICAL_H
