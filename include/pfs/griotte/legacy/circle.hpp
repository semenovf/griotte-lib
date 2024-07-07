#pragma once
#include <pfs/griotte/point.hpp>

namespace pfs {
namespace griotte {

template <typename UnitT>
class circle
{
    using unit_type = UnitT;
    using point_type = point<unit_type>;

    point_type _center;
    unit_type  _radius;

public:
    /**
     * @brief Constructs a null circle (with zero coordinates).
     */
    constexpr circle () noexcept : _radius(0) {}

    /**
     * @brief Constructs a circle with center at (@a cx, @a cy) and with
     *        radius @a radius.
     */
    constexpr circle (unit_type cx
            , unit_type cy
            , unit_type radius) noexcept
        : _center(cx, cy)
        , _radius(radius)
    {}

    /**
     * @brief Constructs a circle with center at @a center point and with
     *        radius @a radius.
     */
    constexpr circle (point_type const & center
            , unit_type radius) noexcept
        : _center(center)
        , _radius(radius)
    {}

    ~circle () = default;
    circle (circle const & rhs) = default;
    circle & operator = (circle const & rhs) = default;
    circle (circle && rhs) = default;
    circle & operator = (circle && rhs) = default;

    /**
     * @return The circle's center point.
     */
    constexpr inline point_type get_center () const noexcept
    {
        return _center;
    }

    /**
     * @return The circle's radius.
     */
    constexpr inline unit_type get_radius () const noexcept
    {
        return _radius;
    }
};

}} // namespace pfs::griotte


