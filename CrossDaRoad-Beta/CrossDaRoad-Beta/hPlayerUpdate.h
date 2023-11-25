#ifndef H_PLAYER_UPDATE_H
#define H_PLAYER_UPDATE_H

// forward declaration
class hPlayer;

class hPlayerUpdate
{
private: // Dependency
	hPlayer* ptrPlayer;

public: // Constructors & Destructor
	hPlayerUpdate();
	hPlayerUpdate(hPlayer* ptrPlayer);
	~hPlayerUpdate();

public: // Initializer & Clean-up
	bool SetupTarget(hPlayer* ptrPlayer);

public: // Logic Updater
	bool OnUpdatePlayerIdle();
	bool OnUpdatePlayerJumpStart();
	bool OnUpdatePlayerJumpContinue() const;
	bool OnUpdatePlayerJumpStop();

public:
	bool OnUpdate();
};

#endif // H_PLAYER_UPDATE_H
