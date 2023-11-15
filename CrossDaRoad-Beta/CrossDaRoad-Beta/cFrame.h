#ifndef C_FRAME_H
#define C_FRAME_H

#include <iostream>

template<const size_t FRAME_LIMIT, const int ID_BASE = 1>
class cFrame
{
public:
    float fVal;

public: /// Constructors & Destructor
    cFrame(float val = 0)
        : fVal(val) {}

    ~cFrame()
    {
        std::cerr << "cFrame<size=" << FRAME_LIMIT << "> got destructed: ";
        std::cerr << "properties{ fVal=" << fVal << " }" << std::endl;
        fVal = 0;
    }

public: /// Initialization & Clean-up
    bool Reset()
    {
        fVal = 0;
        return true;
    }

public: /// Checkers & Validators
    bool IsValidID(int nID) const
    {
        return (GetMinID() <= nID) && (nID <= GetMaxID());
    }

public: /// Getters
    int GetID() const
    {
        return GetTickID() % FRAME_LIMIT + ID_BASE;
    }

    int GetTickID() const
    {
        return static_cast<int>(fVal);
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

    float GetFrameTick(const int nFrameDelay, const float fTickRate = 0.01f) const
    {
        return (24.0f / FRAME_LIMIT) / (nFrameDelay * fTickRate);
    }

public: /// Setters
    void SetVal(float val)
    {
        fVal = val;
    }

public: /// Updaters
    bool Update(const float fTickTime, const int nFrameDelay, const float fTickRate = 0.01f)
    {
        float fFrameTick = GetFrameTick(nFrameDelay, fTickRate);
        SetVal(fTickTime / fFrameTick);
        return true;
    }
};

using frame4_t = cFrame<4>;
using frame6_t = cFrame<6>;
using frame8_t = cFrame<8>;

#endif // C_FRAME_H
