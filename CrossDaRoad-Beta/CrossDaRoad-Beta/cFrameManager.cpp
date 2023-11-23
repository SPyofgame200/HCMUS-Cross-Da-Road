#include "cFrameManager.h"

frame4_t cFrameManager::frame4;
frame6_t cFrameManager::frame6;
frame8_t cFrameManager::frame8;
frame12_t cFrameManager::frame12;

cFrameManager cFrameManager::frameManager;

cFrameManager::cFrameManager() : fTimeSinceStart(0.0f), nFrameDelay(0)
{
    Reset();
}

cFrameManager::~cFrameManager()
{
}

cFrameManager& cFrameManager::GetInstance()
{
    return frameManager;
}

frame4_t& cFrameManager::GetFrame4()
{
    return frame4;
}

frame6_t& cFrameManager::GetFrame6()
{
    return frame6;
}

frame8_t& cFrameManager::GetFrame8()
{
    return frame8;
}

frame12_t& cFrameManager::GetFrame12()
{
    return frame12;
}

void cFrameManager::Reset()
{
    frame4.Reset();
    frame6.Reset();
    frame8.Reset();
    frame12.Reset();
}

int cFrameManager::GetFrameID(const int frame) const
{
    if (frame == frame4.GetLimit()) return frame4.GetID();
    else if (frame == frame6.GetLimit()) return frame6.GetID();
    else if (frame == frame8.GetLimit()) return frame8.GetID();
    else if (frame == frame12.GetLimit()) return frame12.GetID();
    return 0;
}

int cFrameManager::GetFrameID(const int frame, float fTickRate) const
{
    if (frame == frame4.GetLimit()) return frame4.GetID();
    else if (frame == frame6.GetLimit()) return frame6.GetID();
    else if (frame == frame8.GetLimit()) return frame8.GetID();
    else if (frame == frame12.GetLimit()) return frame12.GetID();
    return 0;
}

std::string cFrameManager::ShowFrameID(const int frame) const
{
    if (frame <= 0) return "";
    return std::to_string(GetFrameID(frame));
}

std::string cFrameManager::ShowFrameID(const int frame, float fTickRate) const
{
    if (frame <= 0) return "";
    return std::to_string(GetFrameID(frame, fTickRate));
}

bool cFrameManager::UpdateFrame(float fTickTime, int nFrameDelay, float fTickRate)
{
    this->fTimeSinceStart = fTickTime;
    this->nFrameDelay = nFrameDelay;
    frame4.UpdateFrame(fTickTime, nFrameDelay, fTickRate);
    frame6.UpdateFrame(fTickTime, nFrameDelay, fTickRate);
    frame8.UpdateFrame(fTickTime, nFrameDelay, fTickRate);
    frame12.UpdateFrame(fTickTime, nFrameDelay, fTickRate);
    return true;
}
