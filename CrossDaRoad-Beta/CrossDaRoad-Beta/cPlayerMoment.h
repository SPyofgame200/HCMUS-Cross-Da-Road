#ifndef C_PLAYER_MOMENT_H
#define C_PLAYER_MOMENT_H

#include "cFrame.h"

class cPlayerMoment
{
private: /// Properties
	int frame6_id_animation_safe;
	frame6_t frame;

public: /// Constructors & Destructor
	cPlayerMoment();

public: /// Initializer & Clean-up
	void Reset();

public:
	bool StartAnimation();
	bool NextAnimation(bool bUpdate = true);

public: /// Getters
	int GetLimit() const;
	int GetSafeAnimationID() const;
	int GetAnimationID() const;
	bool IsValidID(int nID) const;

public: /// Checkers
	bool IsJumpingStop() const;
	bool IsJumpingSafe() const;
};

#endif // C_PLAYER_MOMENT_H
