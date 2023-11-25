#include "cPlayerAction.h"

cPlayerAction::cPlayerAction()
{
    Reset();
}

void cPlayerAction::Reset()
{
    nActionFlag = NONE;
}

void cPlayerAction::Modify(Action action, bool bValue)
{
    return (bValue == true) ? Insert(action) : Remove(action);
}

void cPlayerAction::Insert(Action action)
{
    nActionFlag |= static_cast<int>(action);
}

void cPlayerAction::Remove(Action action)
{
    nActionFlag &= ~static_cast<int>(action);
}

void cPlayerAction::Toggle(Action action)
{
    nActionFlag ^= static_cast<int>(action);
}

void cPlayerAction::Modify(std::initializer_list<Action> actions, bool bValue)
{
    for (Action action : actions) {
        Modify(action, bValue);
    }
}

void cPlayerAction::Insert(std::initializer_list<Action> actions)
{
    for (Action action : actions) {
        Insert(action);
    }
}

void cPlayerAction::Remove(std::initializer_list<Action> actions)
{
    for (Action action : actions) {
        Remove(action);
    }
}

void cPlayerAction::Toggle(std::initializer_list<Action> actions)
{
    for (Action action : actions) {
        Toggle(action);
    }
}

bool cPlayerAction::IsMove() const
{
    return nActionFlag != NONE;
}

bool cPlayerAction::IsMove(Action action) const
{
    return (nActionFlag & static_cast<int>(action)) != 0;
}

bool cPlayerAction::IsMove(std::initializer_list<Action> actions) const
{
    for (Action action : actions) {
        if (IsMove(action)) {
            return true;
        }
    }
    return false;
}

bool cPlayerAction::IsMoveLeft() const
{
    return IsMove(LEFT);
}
bool cPlayerAction::IsMoveRight() const
{
    return IsMove(RIGHT);
}
bool cPlayerAction::IsMoveUp() const
{
    return IsMove(UP);
}
bool cPlayerAction::IsMoveDown() const
{
    return IsMove(DOWN);
}