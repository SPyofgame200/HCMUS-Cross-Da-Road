#include "cFrameManager.h"

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
    return frame4_t::GetSharedInstance();
}

frame6_t& cFrameManager::GetFrame6()
{
    return frame6_t::GetSharedInstance();
}

frame8_t& cFrameManager::GetFrame8()
{
    return frame8_t::GetSharedInstance();
}

frame12_t& cFrameManager::GetFrame12()
{
    return frame12_t::GetSharedInstance();
}

void cFrameManager::Reset()
{
    GetFrame4().Reset();
    GetFrame6().Reset();
    GetFrame8().Reset();
    GetFrame12().Reset();
}

int cFrameManager::GetFrameID(const int frame) const
{
    if (frame == GetFrame4().FrameLimit()) return GetFrame4().GetID();
    if (frame == GetFrame6().FrameLimit()) return GetFrame6().GetID();
    if (frame == GetFrame8().FrameLimit()) return GetFrame8().GetID();
    if (frame == GetFrame12().FrameLimit()) return GetFrame12().GetID();
    return 0;
}

int cFrameManager::GetFrameID(const int frame, float fTickRate) const
{
    if (frame == GetFrame4().FrameLimit()) {
        frame4_t current = GetFrame4();
        current.UpdateFrame(fTimeSinceStart, nFrameDelay, fTickRate);
        return current.GetID();
    }
    if (frame == GetFrame6().FrameLimit()) {
        frame6_t current = GetFrame6();
        current.UpdateFrame(fTimeSinceStart, nFrameDelay, fTickRate);
        return current.GetID();
    }
    if (frame == GetFrame8().FrameLimit()) {
        frame8_t current = GetFrame8();
        current.UpdateFrame(fTimeSinceStart, nFrameDelay, fTickRate);
        return current.GetID();
    }
    if (frame == GetFrame12().FrameLimit()) {
        frame12_t current = GetFrame12();
        current.UpdateFrame(fTimeSinceStart, nFrameDelay, fTickRate);
        return current.GetID();
    }
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
    GetFrame4().UpdateFrame(fTickTime, nFrameDelay, fTickRate);
    GetFrame6().UpdateFrame(fTickTime, nFrameDelay, fTickRate);
    GetFrame8().UpdateFrame(fTickTime, nFrameDelay, fTickRate);
    GetFrame12().UpdateFrame(fTickTime, nFrameDelay, fTickRate);
    return true;
}
