#pragma once
#include <pfs/griotte/unit.hpp>

namespace pfs {
namespace griotte {

template <typename UnitT>
class rect
{
    using unit_type = UnitT;

    unit_type _x1;
    unit_type _y1;
    unit_type _x2;
    unit_type _y2;

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
    constexpr rect (unit_type x
                , unit_type y
                , unit_type width
                , unit_type height) noexcept
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
    constexpr inline unit_type x () const noexcept
    {
        return _x1;
    }

    /**
     * @return The y-coordinate of the rectangle's left edge.
     */
    constexpr inline unit_type y () const noexcept
    {
        return _y1;
    }

    /**
     * @return The width of the rectangle.
     */
    constexpr inline unit_type width () const noexcept
    {
        return _x2 - _x1 + 1;
    }

    /**
     * @return The height of the rectangle.
     */
    constexpr inline unit_type height () const noexcept
    {
        return _y2 - _y1 + 1;
    }

    /**
     * @return @c true if the point (@a x, @a y) is inside this rectangle
     *         including on the edge, otherwise returns @c false.
     */
    constexpr inline bool contains (unit_type x
            , unit_type y) const noexcept
    {
        return (x < _x1
                || x > _x2
                || y < _y1
                || y > _y2) ? false : true;
    }

    /**
     * @return @c true if the point (@a x, @a y) is inside this rectangle
     *         excluding on the edge, otherwise returns @c false.
     */
    constexpr inline bool contains_exclude_edge (unit_type x
            , unit_type y) const noexcept
    {
        return (x <= _x1
                || x >= _x2
                || y <= _y1
                || y >= _y2) ? false : true;
    }
};

}} // namespace pfs::griotte
