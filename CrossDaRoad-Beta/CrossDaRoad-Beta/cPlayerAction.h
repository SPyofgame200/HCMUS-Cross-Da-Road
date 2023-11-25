#ifndef C_PLAYER_ACTION
#define C_PLAYER_ACTION

#include <initializer_list>

class cPlayerAction
{
public:
	enum Action
	{
		NONE	= 0,
		LEFT	= 1,
		RIGHT	= 2,
		UP		= 4,
		DOWN	= 8,
	};

	using flag_t = int;

private:
	flag_t nActionFlag;

public: // Constructors & Destructor
	cPlayerAction();

public: // Initializer & Clean-up
	void Reset();

public: // Single Action
	void Insert(Action);
	void Remove(Action);
	void Toggle(Action);

public: // Chained Actions
	void Insert(std::initializer_list<Action> actions);
	void Remove(std::initializer_list<Action> actions);
	void Toggle(std::initializer_list<Action> actions);

public: /// Checkers
	bool IsMove() const;
	bool IsMove(Action) const;
	bool IsMove(std::initializer_list<Action> actions) const;
	bool IsMoveLeft() const;
	bool IsMoveRight() const;
	bool IsMoveUp() const;
	bool IsMoveDown() const;
};

using PlayerAction = cPlayerAction::Action;

#endif C_PLAYER_ACTION
