#pragma once
#include <pfs/math/round.hpp>
#include <pfs/griotte/unit.hpp>

namespace pfs {
namespace griotte {

class point
{
    unit_t _x;
    unit_t _y;

public:
    /**
     * @brief Constructs a point with coordinates (0, 0).
     */
    constexpr point () noexcept
        : _x(0)
        , _y(0)
    {}

    /**
     * @brief Constructs a point with the given coordinates (@a x, @a y).
     */
    constexpr point (unit_t x, unit_t y) noexcept
        : _x(x)
        , _y(y)
    {}

    point (point const & rhs) = default;
    point & operator = (point const & rhs) = default;

    /**
     * @return The @c x coordinate of this point.
     */
    constexpr inline unit_t x () const noexcept
    {
        return _x;
    }

    /**
     * @return The @c y coordinate of this point.
     */
    constexpr inline unit_t y () const noexcept
    {
        return _y;
    }

    /**
     * @brief Sets the @c x coordinate of this point to the given @a x coordinate.
     */
    inline void set_x (unit_t x) noexcept
    {
        _x = x;
    }

    /**
     * @brief Sets the @c y coordinate of this point to the given @a y coordinate.
     */
    inline void set_y (unit_t y) noexcept
    {
        _y = y;
    }

    /**
     * @brief Increments @c x by @a dx.
     */
    inline void increment_x (int dx) noexcept
    {
        _x += dx;
    }

    /**
     * @brief Increments @c y by @a dy.
     */
    inline void increment_y (int dy) noexcept
    {
        _y += dy;
    }

    /**
     * @brief Increments @c x and @c y by @a dx and @a dy respectively.
     */
    inline void increment (int dx, int dy) noexcept
    {
        _x += dx;
        _y += dy;
    }

    /**
     * @brief Adds the given point to this point.
     * @return A reference to this point.
     */
    inline point & operator += (point const & p) noexcept
    {
        _x += p._x;
        _y += p._y;
        return *this;
    }

    /**
     * @brief Subtracts the given point from this point.
     * @return A reference to this point.
     */
    inline point & operator -= (point const & p) noexcept
    {
        _x -= p._x;
        _y -= p._y;
        return *this;
    }

    /**
     * @brief Multiplies this point's coordinates by the given factor.
     * @return A reference to this point.
     * @note The result is rounded to the nearest integer if points are held as integers.
     */
    inline point & operator *= (float factor) noexcept
    {
        _x = pfs::round(_x * factor);
        _y = pfs::round(_y * factor);
        return *this;
    }

    /**
     * @brief Multiplies this point's coordinates by the given factor.
     * @return A reference to this point.
     */
    inline point & operator *= (double factor) noexcept
    {
        _x = pfs::round(_x * factor);
        _y = pfs::round(_y * factor);
        return *this;
    }

    /**
     * @brief Multiplies this point's coordinates by the given factor.
     * @return A reference to this point.
     */
    inline point & operator *= (int factor) noexcept
    {
        _x *= factor;
        _y *= factor;
        return *this;
    }
};

#ifdef PFS_GRIOTTE_SOURCE

#endif

}} // namespace pfs::griotte

