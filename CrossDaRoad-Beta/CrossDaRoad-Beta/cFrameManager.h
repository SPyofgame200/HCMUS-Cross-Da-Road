// cFrameManager.h

#ifndef C_FRAME_MANAGER_H
#define C_FRAME_MANAGER_H

#include <string>
#include "cFrame.h"

class cFrameManager
{
public: /// Properties
    static frame4_t& GetFrame4();
    static frame6_t& GetFrame6();
    static frame8_t& GetFrame8();
    static frame12_t& GetFrame12();

private: /// Instance
    static cFrameManager frameManager;

public:
    static cFrameManager& GetInstance();

private: // Timer
    float fTimeSinceStart;
    int nFrameDelay;

private:
    cFrameManager();
    ~cFrameManager();

public: /// Setters & Reseters
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
