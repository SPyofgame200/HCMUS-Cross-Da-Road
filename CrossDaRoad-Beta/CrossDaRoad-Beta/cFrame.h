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
    static cFrame& GetSharedInstance(Args&&... args);
public: /// Constructors & Destructor
    cFrame(float fInitTime = 0);
    ~cFrame();

public: /// Initialization & Clean-up
    bool Reset();

public: /// Interface Getters
    static float GetFrameTick(const int nFrameDelay, const float fTickRate);
    static int GetID(int nTickID);
    static int GetID(float fTickID);
    static int GetMinID();
    static int GetMaxID();
    static int GetDefaultID();
    static int GetLimit();
    
public: /// Checkers & Validators
    bool IsValidID(int nID) const;

public: /// Animation updaters
    bool UpdateTime(float fCurrentTime);
    bool UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate = 0.001f);
    bool UpdateLocal();

public: /// Animation getters
    int GetAnimationID() const;
    int GetID() const;
    int GetTickID() const;

public: /// Animation checker
    bool IsStartAnimation();
    bool IsStopAnimation();

public: /// Animation Control
    bool StartAnimation();
    bool NextAnimation(bool bSlowUpdate = true, bool bUpdate = true);
    bool StopAnimation();

public: /// Input - Output
    void Read(std::istream& input);
    void Write(std::ostream& output) const;
};

using frame4_t = cFrame<4>;
using frame6_t = cFrame<6>;
using frame8_t = cFrame<8>;
using frame12_t = cFrame<12>;

#endif // C_FRAME_H