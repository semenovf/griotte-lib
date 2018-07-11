#pragma once
#include <pfs/griotte/unit.hpp>

namespace pfs {
namespace griotte {

class rect
{
    unit_t _x1;
    unit_t _y1;
    unit_t _x2;
    unit_t _y2;

public:
    /**
     * @brief Constructs a null rectangle (with zero coordinates).
     */
    constexpr rect () noexcept
        : _x1(0)
        , _y1(0)
        , _x2(-1)
        , _y2(-1)
    {}

    /**
     * @brief Constructs a rectangle with (x, y) as its top-left corner
     *        and the given width and height.
     */
    constexpr rect (unit_t x, unit_t y, unit_t width, unit_t height) noexcept
        : _x1(x)
        , _y1(y)
        , _x2(x + width - 1)
        , _y2(y + height - 1)
    {}

    rect (rect const & rhs) = default;
    rect & operator = (rect const & rhs) = default;

    /**
     * @return The x-coordinate of the rectangle's left edge.
     */
    constexpr inline unit_t x () const noexcept
    {
        return _x1;
    }

    /**
     * @return The y-coordinate of the rectangle's left edge.
     */
    constexpr inline unit_t y () const noexcept
    {
        return _y1;
    }

    /**
     * @return The width of the rectangle.
     */
    constexpr inline unit_t width () const noexcept
    {
        return _x2 - _x1 + 1;
    }

    /**
     * @return The height of the rectangle.
     */
    constexpr inline unit_t height () const noexcept
    {
        return _y2 - _y1 + 1;
    }

    /**
     * @return @c true if the point (@a x, @a y) is inside this rectangle
     *         including on the edge, otherwise returns @c false.
     */
    inline bool contains (unit_t x, unit_t y) const noexcept;

    /**
     * @return @c true if the point (@a x, @a y) is inside this rectangle
     *         excluding on the edge, otherwise returns @c false.
     */
    inline bool contains_exclude_edge (unit_t x, unit_t y) const noexcept;
};

inline bool rect::contains (unit_t x, unit_t y) const noexcept
{
    return (x < _x1
            || x > _x2
            || y < _y1
            || y > _y2) ? false : true;
}

inline bool rect::contains_exclude_edge (unit_t x, unit_t y) const noexcept
{
    return (x <= _x1
            || x >= _x2
            || y <= _y1
            || y >= _y2) ? false : true;
}

#ifdef PFS_GRIOTTE_SOURCE

#endif

}} // namespace pfs::griotte
