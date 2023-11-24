#ifndef H_PLAYER_HITBOX_H
#define H_PLAYER_HITBOX_H

// forward declaration
class hPlayer;

class hPlayerHitbox
{
private: // Dependency
	hPlayer* ptrPlayer;

public: // Constructors & Destructor
	hPlayerHitbox();
	hPlayerHitbox(hPlayer* ptrPlayer);
	~hPlayerHitbox();

public: // Initializer & Clean-up
	bool SetupTarget(hPlayer* ptrPlayer);

};

#endif // H_PLAYER_HITBOX_H
