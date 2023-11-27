#include "cFrame.h"

#define EXPLICIT_INSTANTIATION(n) \
   template cFrame<n>& cFrame<n>::GetSharedInstance(); \
   template cFrame<n>::cFrame(float fInitTime); \
   template cFrame<n>::~cFrame(); \
   template bool cFrame<n>::Reset(); \
   template bool cFrame<n>::IsValidID(int nID) const; \
   template int cFrame<n>::GetID(int nTickID); \
   template int cFrame<n>::GetID(float fTickID); \
   template int cFrame<n>::GetMinID(); \
   template int cFrame<n>::GetMaxID(); \
   template float cFrame<n>::GetFrameTick(const int nFrameDelay, const float fTickRate); \
   template int cFrame<n>::GetDefaultID(); \
   template int cFrame<n>::GetLimit(); \
   template void cFrame<n>::UpdateTime(float fCurrentTime); \
   template bool cFrame<n>::UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate); \
   template int cFrame<n>::GetAnimationID() const; \
   template int cFrame<n>::GetID() const; \
   template int cFrame<n>::GetTickID() const; \
   template bool cFrame<n>::IsStartAnimation(); \
   template bool cFrame<n>::IsStopAnimation(); \
   template bool cFrame<n>::StartAnimation(); \
   template bool cFrame<n>::NextAnimation(bool bSlowUpdate, bool bUpdate); \
   template bool cFrame<n>::StopAnimation();

EXPLICIT_INSTANTIATION(4)
EXPLICIT_INSTANTIATION(6)
EXPLICIT_INSTANTIATION(8)
EXPLICIT_INSTANTIATION(12)

#undef EXPLICIT_INSTANTIATION(n)

template<const size_t FRAME_LIMIT>
template<typename... Args>
cFrame<FRAME_LIMIT>& cFrame<FRAME_LIMIT>::GetSharedInstance(Args&&... args)
{
    static cFrame instance(std::forward<Args>(args)...); // Create a static instance
    return instance;
}

template<const size_t FRAME_LIMIT>
cFrame<FRAME_LIMIT>::cFrame(float fInitTime)
    : fTime(fInitTime), fStart(0), nAnimationFrame(0)
{
    // ...
}

template<const size_t FRAME_LIMIT>
cFrame<FRAME_LIMIT>::~cFrame()
{
    //std::cerr << "cFrame<size=" << FRAME_LIMIT << "> got destructed: ";
    //std::cerr << "properties{ fTime=" << fTime << " }" << std::endl;
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::Reset()
{
    fTime = 0;
    return true;
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::IsValidID(int nID) const
{
    return (GetMinID() <= nID) && (nID <= GetMaxID());
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetID(int nTickID)
{
    return nTickID % FRAME_LIMIT + ID_BASE;
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetID(float fTickID)
{
    return GetID(static_cast<int>(std::floor(fTickID)));
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetMinID()
{
    return ID_BASE;
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetMaxID()
{
    return ID_BASE + FRAME_LIMIT - 1;
}

template<const size_t FRAME_LIMIT>
float cFrame<FRAME_LIMIT>::GetFrameTick(const int nFrameDelay, const float fTickRate)
{
    return (24.0f / FRAME_LIMIT) / (nFrameDelay * fTickRate);
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetDefaultID()
{
    return ID_BASE - 1;
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetLimit()
{
    return static_cast<int>(FRAME_LIMIT);
}

template<const size_t FRAME_LIMIT>
void cFrame<FRAME_LIMIT>::UpdateTime(float fCurrentTime)
{
    fTime = fCurrentTime;
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate)
{
    const float fFrameTick = GetFrameTick(nFrameDelay, fTickRate);
    UpdateTime(fTickTime / fFrameTick);
    return true;
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetAnimationID() const
{
    return GetID(fTime - fStart);
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetID() const
{
    return GetID(GetTickID());
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetTickID() const
{
    return static_cast<int>(fTime);
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::IsStartAnimation()
{
    return nAnimationFrame == GetDefaultID();
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::IsStopAnimation()
{
    return nAnimationFrame >= GetMaxID();
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::StartAnimation()
{
    fStart = fTime;
    nAnimationFrame = GetDefaultID();
    return true;
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::NextAnimation(bool bSlowUpdate, bool bUpdate)
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

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::StopAnimation()
{
    nAnimationFrame = GetMaxID();
    return true;
}
