#ifndef U_APP_UTILS_H
#define U_APP_UTILS_H

namespace utils
{
    template<class T>
    constexpr const T& Min(const T& a, const T& b)
    {
        return b < a ? b : a;
    }

    template<class T>
    constexpr const T& Max(const T& a, const T& b)
    {
        return a < b ? b : a;
    }

    template<class T>
    constexpr const T& Clamp(const T& v, const T& lo, const T& hi)
    {
        return Max(lo, Min(v, hi));
    }
}

#endif // U_APP_UTILS_H
