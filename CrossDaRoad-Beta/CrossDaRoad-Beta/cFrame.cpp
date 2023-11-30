#include "cFrame.h"

#define EXPLICIT_INSTANTIATION(n) \
    template cFrame<n>& cFrame<n>::GetSharedInstance(); \
    template cFrame<n>::cFrame(float fInitTime); \
    template cFrame<n>::~cFrame(); \
    template bool cFrame<n>::Reset(); \
    template float cFrame<n>::CalculateFrameTick(const int nFrameDelay, const float fTickRate); \
    template int cFrame<n>::CalculateID(int nTickID); \
    template int cFrame<n>::CalculateID(float fTickID); \
    template int cFrame<n>::MinID(); \
    template int cFrame<n>::MaxID(); \
    template int cFrame<n>::DefaultID(); \
    template int cFrame<n>::FrameLimit(); \
    template bool cFrame<n>::IsValidID(int nID) const; \
    template bool cFrame<n>::UpdateTime(float fCurrentTime); \
    template bool cFrame<n>::UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate); \
    template bool cFrame<n>::UpdateLocal(); \
    template int cFrame<n>::GetAnimationID() const; \
    template int cFrame<n>::GetID() const; \
    template int cFrame<n>::GetTickID() const; \
    template bool cFrame<n>::IsStartAnimation(); \
    template bool cFrame<n>::IsStopAnimation(); \
    template bool cFrame<n>::StartAnimation(); \
    template bool cFrame<n>::NextAnimation(bool bSlowUpdate, bool bUpdate); \
    template bool cFrame<n>::StopAnimation(); \
    template void cFrame<n>::Read(std::istream& input); \
    template void cFrame<n>::Write(std::ostream& output) const; \

EXPLICIT_INSTANTIATION(4);
EXPLICIT_INSTANTIATION(6);
EXPLICIT_INSTANTIATION(8);
EXPLICIT_INSTANTIATION(12);

#undef EXPLICIT_INSTANTIATION

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////// INSTANCE ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<const size_t FRAME_LIMIT>
template<typename... Args>
cFrame<FRAME_LIMIT>& cFrame<FRAME_LIMIT>::GetSharedInstance(Args&&... args)
{
	static cFrame instance(std::forward<Args>(args)...); // Create a static instance
	return instance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// CONSTRUCTOR & DESTRUCTOR ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// RESETER ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::Reset()
{
	fTime = 0;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////// CORE /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::StartAnimation()
{
	fStart = fTime;
	nAnimationFrame = DefaultID();
	return true;
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::NextAnimation(bool bSlowUpdate, bool bUpdate)
{
	if (nAnimationFrame < MinID()) {
		if (bUpdate) {
			nAnimationFrame = MinID();
		}
		return true;
	}

	const int nCurrentFrame = utils::Min(GetAnimationID(), MaxID());
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
	nAnimationFrame = MaxID();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// EVALUATION //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<const size_t FRAME_LIMIT>
float cFrame<FRAME_LIMIT>::CalculateFrameTick(const int nFrameDelay, const float fTickRate)
{
	return (24.0f / FRAME_LIMIT) / (nFrameDelay * fTickRate);
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::CalculateID(int nTickID)
{
	return nTickID % FRAME_LIMIT + ID_BASE;
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::CalculateID(float fTickID)
{
	return CalculateID(static_cast<int>(std::floor(fTickID)));
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::MinID()
{
	return ID_BASE;
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::MaxID()
{
	return ID_BASE + FRAME_LIMIT - 1;
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::DefaultID()
{
	return ID_BASE - 1;
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::FrameLimit()
{
	return static_cast<int>(FRAME_LIMIT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////// CHECKER ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::IsValidID(int nID) const
{
	return (MinID() <= nID) && (nID <= MaxID());
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::IsStartAnimation()
{
	return nAnimationFrame == DefaultID();
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::IsStopAnimation()
{
	return nAnimationFrame >= MaxID();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// GETTER ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetAnimationID() const
{
	return CalculateID(fTime - fStart);
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetID() const
{
	return CalculateID(GetTickID());
}

template<const size_t FRAME_LIMIT>
int cFrame<FRAME_LIMIT>::GetTickID() const
{
	return static_cast<int>(fTime);
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::UpdateTime(float fCurrentTime)
{
	fTime = fCurrentTime;
	return true;
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate)
{
	const float fFrameTick = CalculateFrameTick(nFrameDelay, fTickRate);
	return UpdateTime(fTickTime / fFrameTick);
}

template<const size_t FRAME_LIMIT>
bool cFrame<FRAME_LIMIT>::UpdateLocal()
{
	fTime = GetSharedInstance().fTime;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// INPUT & OUTPUT ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<const size_t FRAME_LIMIT>
void cFrame<FRAME_LIMIT>::Read(std::istream& input) {
	input >> fTime >> fStart >> nAnimationFrame;
}

template<const size_t FRAME_LIMIT>
void cFrame<FRAME_LIMIT>::Write(std::ostream& output) const {
	output << fTime << " " << fStart << " " << nAnimationFrame;
}