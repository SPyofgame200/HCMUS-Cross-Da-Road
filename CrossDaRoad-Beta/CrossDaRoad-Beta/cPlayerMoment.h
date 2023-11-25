#ifndef C_PLAYER_MOMENT_H
#define C_PLAYER_MOMENT_H

class cPlayerMoment
{
private: /// Properties
	int frame6_id_animation_safe;

public: /// Constructors & Destructor
	cPlayerMoment();

public: /// Initializer & Clean-up
	void Reset();

public: /// Getters
	int GetSafeAnimationID() const;

public: /// Checkers
	bool IsPlayerLanding() const;
};

#endif // C_PLAYER_MOMENT_H
