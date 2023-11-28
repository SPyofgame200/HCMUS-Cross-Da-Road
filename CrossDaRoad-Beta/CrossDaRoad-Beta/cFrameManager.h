// cFrameManager.h

#ifndef C_FRAME_MANAGER_H
#define C_FRAME_MANAGER_H

#include <string>
#include "cFrame.h"

class cFrameManager
{
private: /// [Static Properties]
    static cFrameManager frameManager;

public: /// [Instance]
    static frame4_t& GetFrame4();
    static frame6_t& GetFrame6();
    static frame8_t& GetFrame8();
    static frame12_t& GetFrame12();
    static cFrameManager& GetInstance();

private: // [Properties]: Timer
    float fTimeSinceStart;
    int nFrameDelay;

private: /// [Constructor] - [Destructor]
    cFrameManager();
    ~cFrameManager();

public: /// [Reseter]
    void Reset();

public: /// Getters
    int GetFrameID(int frame) const;
    int GetFrameID(int frame, float fTickRate) const;

public: /// Frame output
    std::string ShowFrameID(int frame) const;
    std::string ShowFrameID(int frame, float fTickRate) const;

    bool UpdateFrame(float fTickTime, int nFrameDelay, float fTickRate = 0.01f);
};

#endif // C_FRAME_MANAGER_H
