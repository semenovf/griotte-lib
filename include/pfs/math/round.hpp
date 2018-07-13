#pragma once
#include <cmath>

namespace pfs {

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

/**
 * @return The rounded (nearest) integer value.
 */
constexpr inline long int lround (float x)
{
    return std::lround(x);
}

/**
 * @return The rounded (nearest) integer value.
 */
constexpr inline long int lround (double x)
{
    return std::lround(x);
}

/**
 * @return The rounded (nearest) integer value.
 */
constexpr inline long int lround (long double x)
{
    return std::lround(x);
}

} // namespace pfs
