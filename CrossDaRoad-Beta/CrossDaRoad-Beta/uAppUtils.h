/**
 * @file uAppUtils.h
 * @brief Contains application utilities
 *
**/

#ifndef U_APP_UTILS_H
#define U_APP_UTILS_H

/// @brief Namespace for application utilities 
namespace utils
{
    /// @brief Returns the minimum of two values
    /// @tparam T Type of values
    /// @param a First value
    /// @param b Second value
    /// @return Minimum of two values
    template<class T>
    constexpr const T& Min(const T& a, const T& b)
    {
        return b < a ? b : a;
    }

    /// @brief Returns the maximum of two values
    /// @tparam T Type of values
    /// @param a First value
    /// @param b Second value
    /// @return Maximum of two values
    template<class T>
    constexpr const T& Max(const T& a, const T& b)
    {
        return a < b ? b : a;
    }

    /// @brief Returns the clamped value
    /// @tparam T Type of values
    /// @param v Value to clamp
    /// @param lo Lower bound
    /// @param hi Higher bound
    /// @return Clamped value
    template<class T>
    constexpr const T& Clamp(const T& v, const T& lo, const T& hi)
    {
        return Max(lo, Min(v, hi));
    }
}

#endif // U_APP_UTILS_H
