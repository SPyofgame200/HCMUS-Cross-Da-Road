// cFrameManager.h

#ifndef C_FRAME_MANAGER_H
#define C_FRAME_MANAGER_H

#include <string>
#include "cFrame.h"

class cFrameManager
{
private: // Animator
    static frame4_t frame4;
    static frame6_t frame6;
    static frame8_t frame8;
    static frame12_t frame12;

private: /// Instance
    static cFrameManager frameManager;

private: // Timer
    float fTimeSinceStart;
    int nFrameDelay;

private:
    cFrameManager();
    ~cFrameManager();

public:
    static cFrameManager& GetInstance();

    static frame4_t& GetFrame4();
    static frame6_t& GetFrame6();
    static frame8_t& GetFrame8();
    static frame12_t& GetFrame12();

public: /// Setters & Reseters
    void Reset();

public: /// Getters
    int GetFrameID(const int frame) const;
    int GetFrameID(const int frame, float fTickRate) const;

public: /// Frame output
    std::string ShowFrameID(const int frame) const;
    std::string ShowFrameID(const int frame, float fTickRate) const;

    bool UpdateFrame(float fTickTime, int nFrameDelay, float fTickRate = 0.01f);
};

#endif // C_FRAME_MANAGER_H
