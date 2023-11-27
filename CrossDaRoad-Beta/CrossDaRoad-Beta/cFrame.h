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
private: /// Local properties
    float fTime;
    float fStart;
    int nAnimationFrame;

public: /// Shared properties among the same FRAME_LIMIT
    template<typename... Args>
    static cFrame& GetSharedInstance(Args&&... args)
    {
        static cFrame instance(std::forward<Args>(args)...); // Create a static instance
        return instance;
    }

public: /// Constructors & Destructor
    cFrame(float fInitTime = 0)
    : fTime(fInitTime), fStart(0), nAnimationFrame(0)
    {
        // ...
    }

    ~cFrame()
    {
        //std::cerr << "cFrame<size=" << FRAME_LIMIT << "> got destructed: ";
        //std::cerr << "properties{ fTime=" << fTime << " }" << std::endl;
    }

public: /// Initialization & Clean-up
    bool Reset()
    {
        fTime = 0;
        return true;
    }

public: /// Checkers & Validators
    bool IsValidID(int nID) const
    {
        return (GetMinID() <= nID) && (nID <= GetMaxID());
    }

public: /// Interface Getters
    static int GetID(int nTickID)
    {
        return nTickID % FRAME_LIMIT + ID_BASE;
    }

    static int GetID(float fTickID)
    {
        return GetID(static_cast<int>(std::floor(fTickID)));
    }

    static int GetMinID()
    {
        return ID_BASE;
    }

    static int GetMaxID()
    {
        return ID_BASE + FRAME_LIMIT - 1;
    }

    static float GetFrameTick(const int nFrameDelay, const float fTickRate)
    {
        return (24.0f / FRAME_LIMIT) / (nFrameDelay * fTickRate);
    }

    static int GetDefaultID()
    {
        return ID_BASE - 1;
    }

    static int GetLimit()
    {
        return static_cast<int>(FRAME_LIMIT);
    }

public: /// Animation updaters
    void UpdateTime(float fCurrentTime)
    {
        fTime = fCurrentTime;
    }

    bool UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate = 0.001f)
    {
        const float fFrameTick = GetFrameTick(nFrameDelay, fTickRate);
        UpdateTime(fTickTime / fFrameTick);
        return true;
    }

public: /// Animation getters
    int GetAnimationID() const
    {
        return GetID(fTime - fStart);
    }
    
    int GetID() const
    {
        return GetID(GetTickID());
    }

    int GetTickID() const
    {
        return static_cast<int>(fTime);
    }

public: /// Animation checker
    bool IsStartAnimation()
    {
        return nAnimationFrame == GetDefaultID();
    }

    bool IsStopAnimation()
    {
        return nAnimationFrame >= GetMaxID();
    }

public: /// Animation Control
    bool StartAnimation()
    {
        fStart = fTime;
        nAnimationFrame = GetDefaultID();
        return true;
    }
    bool NextAnimation(bool bSlowUpdate = true, bool bUpdate = true)
    {
        if (nAnimationFrame < GetMinID()) {
            if (bUpdate) {
                nAnimationFrame = GetMinID();
            }
            return true;
        }

        const int nCurrentFrame = utils::Min(GetAnimationID(), GetMaxID());
        if (nAnimationFrame >= nCurrentFrame) {
            return false;
        }
        if (bUpdate) {
            if (bSlowUpdate) {
                nAnimationFrame++;
            }
            else {
                nAnimationFrame = nCurrentFrame;
            }
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
using frame12_t = cFrame<12>;

#endif // C_FRAME_H