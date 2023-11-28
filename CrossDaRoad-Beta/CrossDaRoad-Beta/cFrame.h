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
public: // [Instance] Shared properties among the objects with the same FRAME_LIMIT
    template<typename... Args>
    static cFrame& GetSharedInstance(Args&&... args);

private: // [Member Property]
    float fTime;
    float fStart;
    int nAnimationFrame;

public: // [Constructor] & [Destructor]
    cFrame(float fInitTime = 0);
    ~cFrame();

public: // [Reseter]
    bool Reset();

public: /// [Core] Animation controls
    bool StartAnimation();
    bool NextAnimation(bool bSlowUpdate = true, bool bUpdate = true);
    bool StopAnimation();

public: /// [Evaluation]
    static float CalculateFrameTick(const int nFrameDelay, const float fTickRate);
    static int CalculateID(int nTickID);
    static int CalculateID(float fTickID);
    static int MinID();
    static int MaxID();
    static int DefaultID();
    static int FrameLimit();

public: // [Checker]
    bool IsValidID(int nID) const;
    bool IsStartAnimation();
    bool IsStopAnimation();

public: /// [Getter]
    int GetAnimationID() const;
    int GetID() const;
    int GetTickID() const;

public: /// [Handler] Animation updates
    bool UpdateTime(float fCurrentTime);
    bool UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate = 0.001f);
    bool UpdateLocal();

public: /// [Input] & [Output]
    void Read(std::istream& input);
    void Write(std::ostream& output) const;
};

using frame4_t = cFrame<4>;
using frame6_t = cFrame<6>;
using frame8_t = cFrame<8>;
using frame12_t = cFrame<12>;

#endif // C_FRAME_H