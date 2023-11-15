#ifndef C_FRAME_H
#define C_FRAME_H

#include <iostream>

template<const size_t FRAME_LIMIT>
class cFrame
{
public:
    int nID;
    int nVal;

public: /// Constructors & Destructor
    cFrame(int id = 0, int val = 0)
        : nID(id), nVal(val) {}

    ~cFrame()
    {
        std::cerr << "cFrame<size=" << FRAME_LIMIT << "> got destructed: ";
        std::cerr << "properties{ nID=" << nID << ",nVal=" << nVal << " }" << std::endl;
        nID = 0;
        nVal = 0;
    }

public: /// Initialization & Clean-up
    bool Reset()
    {
        nID = 0;
        nVal = 0;
        return true;
    }

public: /// Getters
    int GetID() const
    {
        return nID;
    }

    int GetVal() const
    {
        return nVal;
    }

    int GetLimit() const
    {
        return static_cast<int>(FRAME_LIMIT);
    }

public: /// Setters
    void SetID(int id)
    {
        nID = id;
    }

    void SetVal(int val)
    {
        nVal = val;
    }
};

using frame4_t = cFrame<4>;
using frame6_t = cFrame<6>;
using frame8_t = cFrame<8>;

#endif // C_FRAME_H
