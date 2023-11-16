#ifndef C_FRAME_H
#define C_FRAME_H

#include "uAppUtils.h"
#include <iostream>

template<const size_t FRAME_LIMIT, const int ID_BASE = 1>
class cFrame
{
public:
    float fVal;
    float fStart;
    int nAnimationFrame;

public: /// Constructors & Destructor
    cFrame(float val = 0)
        : fVal(val), fStart(0), nAnimationFrame(0)
    {
        // ...
    }

    ~cFrame()
    {
        std::cerr << "cFrame<size=" << FRAME_LIMIT << "> got destructed: ";
        std::cerr << "properties{ fVal=" << fVal << " }" << std::endl;
        fVal = 0;
    }

public: /// Initialization & Clean-up
    bool Reset()
    {
        fVal = 0;
        return true;
    }

public: /// Checkers & Validators
    bool IsValidID(int nID) const
    {
        return (GetMinID() <= nID) && (nID <= GetMaxID());
    }

public: /// Properties Getters
    int GetID(int nTickID) const
    {
        return nTickID % FRAME_LIMIT + ID_BASE;
    }

    int GetID(float fTickID) const
    {
        return GetID(static_cast<int>(std::floor(fTickID)));
    }

    int GetID() const
    {
        return GetID(GetTickID());
    }

    int GetTickID() const
    {
        return static_cast<int>(fVal);
    }

    int GetMinID() const
    {
        return ID_BASE;
    }

    int GetMaxID() const
    {
        return ID_BASE + FRAME_LIMIT - 1;
    }

    int GetLimit() const
    {
        return static_cast<int>(FRAME_LIMIT);
    }

public: /// Properties Setters
    void SetVal(float val)
    {
        fVal = val;
    }

private: /// Utilities
    float GetFrameTick(const int nFrameDelay, const float fTickRate = 0.01f) const
    {
        return (24.0f / FRAME_LIMIT) / (nFrameDelay * fTickRate);
    }

public: /// Updaters
    bool UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate = 0.01f)
    {
        float fFrameTick = GetFrameTick(nFrameDelay, fTickRate);
        SetVal(fTickTime / fFrameTick);
        return true;
    }

public: /// Animations
    int GetAnimationID() const
    {
        return GetID(fVal - fStart);
    }
    bool IsStopAnimation() const
    {
        return nAnimationFrame >= GetMaxID();
    }
    bool StartAnimation()
    {
        fStart = fVal;
        nAnimationFrame = ID_BASE - 1;
        return true;
    }
    bool NextAnimation(bool bUpdate = true)
    {
        int nCurrentFrame = utils::Min(GetAnimationID(), GetMaxID());
        if (nAnimationFrame >= nCurrentFrame) {
            return false;
        }
        if (bUpdate) {
            nAnimationFrame = nCurrentFrame;
        }
        return true;
    }
    bool StopAnimation()
    {
        nAnimationFrame = GetMaxID();
        return true;
    }
};

using frame4_t = cFrame<4>;
using frame6_t = cFrame<6>;
using frame8_t = cFrame<8>;

#endif // C_FRAME_H
