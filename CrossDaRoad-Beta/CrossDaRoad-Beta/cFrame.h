/**
 * @file cFrame.h
 * @brief Contains frame class for frame management
 *
 * This file contains frame class prototype for frame management.
 */

#ifndef C_FRAME_H
#define C_FRAME_H

#include "uAppUtils.h"
#include <iostream>

 //=================================================================================================
 // Include new header files here

 //=================================================================================================

constexpr int ID_BASE = 1; /// using 1-based indexes
template<const size_t FRAME_LIMIT>
class cFrame
{
private:
    static float fTime;
    float fStart;
    int nAnimationFrame;

public: /// Constructors & Destructor
    cFrame(float val = 0)
        :  fStart(0), nAnimationFrame(0)
    {
        // ...
    }

    ~cFrame()
    {
        //std::cerr << "cFrame<size=" << FRAME_LIMIT << "> got destructed: ";
        //std::cerr << "properties{ fTime=" << fTime << " }" << std::endl;
        fTime = 0;
    }

public: /// Initialization & Clean-up
    bool Reset()
    {
        fTime = 0;
        return true;
    }

public: /// Checkers & Validators
    static bool IsValidID(int nID)
    {
        return (GetMinID() <= nID) && (nID <= GetMaxID());
    }

public: /// Properties Getters
    static int GetID(int nTickID)
    {
        return nTickID % FRAME_LIMIT + ID_BASE;
    }

    static int GetID(float fTickID)
    {
        return GetID(static_cast<int>(std::floor(fTickID)));
    }

    int GetID() const
    {
        return GetID(GetTickID());
    }

    int GetTickID() const
    {
        return static_cast<int>(fTime);
    }

    static int GetMinID()
    {
        return ID_BASE;
    }

    static int GetMaxID()
    {
        return ID_BASE + FRAME_LIMIT - 1;
    }

    static int GetLimit()
    {
        return static_cast<int>(FRAME_LIMIT);
    }

public: /// Properties Setters
    static void SetVal(float fCurrentTime)
    {
        fTime = fCurrentTime;
    }

private: /// Utilities
    static float GetFrameTick(const int nFrameDelay, const float fTickRate)
    {
        return (24.0f / FRAME_LIMIT) / (nFrameDelay * fTickRate);
    }

public: /// Updaters
    bool UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate = 0.001f)
    {
        const float fFrameTick = GetFrameTick(nFrameDelay, fTickRate);
        SetVal(fTickTime / fFrameTick);
        return true;
    }

public: /// Animations
    int GetAnimationID() const
    {
        return GetID(fTime - fStart);
    }
    bool IsStopAnimation() const
    {
        std::cout << nAnimationFrame << " " << GetMaxID() << std::endl;
        return nAnimationFrame >= GetMaxID();
    }
    bool StartAnimation()
    {
        fStart = fTime;
        nAnimationFrame = ID_BASE - 1;
        return true;
    }
    bool NextAnimation(bool bUpdate = true)
    {
        const int nCurrentFrame = utils::Min(GetAnimationID(), GetMaxID());
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

template <const size_t FRAME_LIMIT>
float cFrame<FRAME_LIMIT>::fTime = 0.0f;

using frame4_t = cFrame<4>;
using frame6_t = cFrame<6>;
using frame8_t = cFrame<8>;
using frame12_t = cFrame<12>;

#endif // C_FRAME_H