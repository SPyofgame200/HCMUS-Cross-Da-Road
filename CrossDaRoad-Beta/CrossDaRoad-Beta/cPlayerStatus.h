#ifndef C_PLAYER_STATUS
#define C_PLAYER_STATUS

class cPlayerStatus
{
public: /// @brief Direction enumeration for player movement
	enum Direction
	{
		LEFT = 1,			///< Left direction for player movement
		RIGHT = 2, 			///< Right direction for player movement
		LEFT_UP = 3, 		///< Left-up direction for player movement
		RIGHT_UP = 4, 		///< Right-up direction for player movement
		LEFT_DOWN = 5, 		///< Left-down direction for player movement
		RIGHT_DOWN = 6, 	///< Right-down direction for player movement
	};

public: /// @brief Animation enumeration for player animation
	enum Animation
	{
		IDLE = 0,			///< When the player doing nothing
		JUMP = 1,			///< When the player is moving, it jumps
		LAND = 2,			///< When the player stopped jumpings
		MOVE = 3,			///< [Unused] When the player can not jump, for example: sinksand
		SWIM = 4,			///< [Unused] When the player moving in a fluide environment like lakes
		TRAP = 5,			///< [Unused] When the player is locked in a position
	};

public: /// @brief Situation enumeration for player interaction
	enum Situation
	{
		ALIVE = 0,	/// [TODO] When the player is fine
		DEATH = 1,	/// [TODO] When the player is killed
		WIN = 2,	/// [Unused] When the player passed a level
		LOSE = 3,	/// [Unused] When the player died all its life
	};

private: // Status
	Direction eDirection;
	Animation eAnimation;
	Situation eSituation;
	
public:
	cPlayerStatus();

public:
	void Reset();

public: /// Checkers
	bool IsExactDirection(Direction eCompare) const;
	bool IsExactAnimation(Animation eCompare) const;
	bool IsExactSituation(Situation eCompare) const;
	bool IsLeftDirection() const;
	bool IsRightDirection() const;

public: /// Getters
	Direction GetDirection() const;
	Animation GetAnimation() const;
	Situation GetSituation() const;

public: /// Setters
	void SetDirection(Direction eNewDirection);
	void SetAnimation(Animation eNewAnimation);
	void SetSituation(Situation eNewSituation);
};

using PlayerDirection = cPlayerStatus::Direction;
using PlayerAnimation = cPlayerStatus::Animation;
using PlayerSituation = cPlayerStatus::Situation;

#endif C_PLAYER_STATUS

