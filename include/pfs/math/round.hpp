#pragma once
#include <cmath>

namespace pfs {

#if 1
/**
 * @return The rounded (nearest) integer value.
 */
constexpr inline float round (float x)
{
    return std::round(x);
}

/**
 * @return The rounded (nearest) integer value.
 */
constexpr inline double round (double x)
{
    return std::round(x);
}

/**
 * @return The rounded (nearest) integer value.
 */
constexpr inline long double round (long double x)
{
    return std::round(x);
}

#else
constexpr inline float round (float d) noexcept
{
    return d >= 0.0f ? int(d + 0.5f) : int(d - float(int(d-1)) + 0.5f) + int(d-1);
}

constexpr inline double round (double d) noexcept
{
     return d >= 0.0 ? int(d + 0.5) : int(d - double(int(d-1)) + 0.5) + int(d-1);
}

constexpr inline long double round (long double d) noexcept
{
    return d >= 0.0
            ? static_cast<long long int>(d + 0.5)
            : static_cast<long long int>(d - double(static_cast<long long int>(d-1)) + 0.5) + static_cast<long long int>(d-1);
}

#endif

} // namespace pfs
