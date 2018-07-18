#pragma once
#include <pfs/math/round.hpp>

namespace pfs {
namespace griotte {

template <typename UnitT>
class point
{
    using unit_type = UnitT;

    unit_type _x;
    unit_type _y;

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
    constexpr point (unit_type x, unit_type y) noexcept
        : _x(x)
        , _y(y)
    {}

    ~point () = default;
    point (point const & rhs) = default;
    point & operator = (point const & rhs) = default;
    point (point && rhs) = default;
    point & operator = (point && rhs) = default;

    /**
     * @return The @c x coordinate of this point.
     */
    constexpr inline unit_type get_x () const noexcept
    {
        return _x;
    }

    /**
     * @return The @c y coordinate of this point.
     */
    constexpr inline unit_type get_y () const noexcept
    {
        return _y;
    }

    /**
     * @brief Sets the @c x coordinate of this point to the given @a x coordinate.
     */
    inline void set_x (unit_type x) noexcept
    {
        _x = x;
    }

    /**
     * @brief Sets the @c y coordinate of this point to the given @a y coordinate.
     */
    inline void set_y (unit_type y) noexcept
    {
        _y = y;
    }

    /**
     * @brief Increments @c x by @a dx.
     */
    inline void increment_x (unit_type dx) noexcept
    {
        _x += dx;
    }

    /**
     * @brief Increments @c y by @a dy.
     */
    inline void increment_y (unit_type dy) noexcept
    {
        _y += dy;
    }

    /**
     * @brief Increments @c x and @c y by @a dx and @a dy respectively.
     */
    inline void increment (unit_type dx, unit_type dy) noexcept
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
        _x = static_cast<unit_type>(pfs::round(_x * factor));
        _y = static_cast<unit_type>(pfs::round(_y * factor));
        return *this;
    }

    /**
     * @brief Multiplies this point's coordinates by the given factor.
     * @return A reference to this point.
     */
    inline point & operator *= (double factor) noexcept
    {
        _x = static_cast<unit_type>(pfs::round(_x * factor));
        _y = static_cast<unit_type>(pfs::round(_y * factor));
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

    constexpr inline bool operator == (point const & rhs) const
    {
        return _x == rhs._x && _y == rhs._y;
    }

    constexpr inline bool operator != (point const & rhs) const
    {
        return ! operator == (rhs);
    }

    friend inline point operator + (point const & p1, point const & p2) noexcept
    {
        point p{p1};
        p += p2;
        return p;
    }

    friend inline point operator - (point const & p1, point const & p2) noexcept
    {
        point p{p1};
        p -= p2;
        return p;
    }
};

}} // namespace pfs::griotte

