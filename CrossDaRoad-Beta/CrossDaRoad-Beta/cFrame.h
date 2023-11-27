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
    float fTime;
    float fStart;
    int nAnimationFrame;

public:
    template<typename... Args>
    static cFrame& GetSharedInstance(Args&&... args)
    {
        static cFrame instance(std::forward<Args>(args)...); // Create a static instance
        return instance;
    }

public: /// Constructors & Destructor
    cFrame()
        : fTime(0), fStart(0), nAnimationFrame(0)
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
        return static_cast<int>(fTime);
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
    void SetVal(float fCurrentTime)
    {
        fTime = fCurrentTime;
    }

private: /// Utilities
    float GetFrameTick(const int nFrameDelay, const float fTickRate) const
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
        return nAnimationFrame >= GetMaxID();
    }
    bool StartAnimation()
    {
        fStart = fTime;
        nAnimationFrame = ID_BASE - 1;
        return true;
    }
    bool NextAnimation(bool bSlowUpdate = true)
    {
        if (nAnimationFrame < GetMinID()) {
            nAnimationFrame = GetMinID();
            return true;
        }
        const int nCurrentFrame = utils::Min(GetAnimationID(), GetMaxID());
        if (nAnimationFrame >= nCurrentFrame) {
            return false;
        }
        if (bSlowUpdate) {
            nAnimationFrame++;
        }
        else {
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
using frame12_t = cFrame<12>;

#endif // C_FRAME_H