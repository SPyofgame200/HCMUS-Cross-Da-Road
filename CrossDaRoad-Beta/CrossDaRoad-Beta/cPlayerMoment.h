#ifndef C_PLAYER_MOMENT_H
#define C_PLAYER_MOMENT_H

#include <iostream>
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
	bool UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate = 0.001f);
	bool IsStopAnimation() const;

public: /// Getters
	int GetLimit() const;
	int GetSafeAnimationID() const;
	int GetAnimationID() const;

public: /// Checkers
	bool IsValidID(int nID) const;
	bool IsJumpingStop() const;
	bool IsJumpingSafe() const;

public: // Input - Output
	void Read(std::istream& input);
	void Write(std::ostream& output) const;
	friend std::istream& operator>>(std::istream& input, cPlayerMoment& playerMoment);
	friend std::ostream& operator<<(std::ostream& output, const cPlayerMoment& playerMoment);
};

#endif // C_PLAYER_MOMENT_H
