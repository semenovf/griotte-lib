#pragma once
#include <pfs/griotte/point.hpp>

namespace pfs {
namespace griotte {

template <typename UnitT>
class ellipse
{
    using unit_type = UnitT;
    using point_type = point<unit_type>;

    point_type _center;
    unit_type  _rx;
    unit_type  _ry;

public:
    /**
     * @brief Constructs a null line (with zero coordinates).
     */
    constexpr ellipse () noexcept : _rx(0), _ry(0) {}

    /**
     * @brief Constructs a line that represents the line between
     *        (@a x1, @a y1) and (@a x2, @a y2).
     */
    constexpr ellipse (unit_type cx
            , unit_type cy
            , unit_type rx
            , unit_type ry) noexcept
        : _center(cx, cy)
        , _rx(rx)
        , _ry(ry)
    {}

    constexpr ellipse (point_type const & center
            , unit_type rx
            , unit_type ry) noexcept
        : _center(center)
        , _rx(rx)
        , _ry(ry)
    {}

    ~ellipse () = default;
    ellipse (ellipse const & rhs) = default;
    ellipse & operator = (ellipse const & rhs) = default;
    ellipse (ellipse && rhs) = default;
    ellipse & operator = (ellipse && rhs) = default;

    /**
     * @return The ellipse's center point.
     */
    constexpr inline point_type get_center () const noexcept
    {
        return _center;
    }

    /**
     * @return The x-axis radius of the ellipse.
     */
    constexpr inline unit_type get_radius_x () const noexcept
    {
        return _rx;
    }

    /**
     * @return The y-axis radius of the ellipse.
     */
    constexpr inline unit_type get_radius_y () const noexcept
    {
        return _ry;
    }
};

}} // namespace pfs::griotte
