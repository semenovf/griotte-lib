#pragma once
#include <pfs/griotte/point.hpp>

namespace pfs {
namespace griotte {

template <typename UnitT>
class line
{
    using unit_type = UnitT;
    using point_type = point<unit_type>;

    point_type _p1;
    point_type _p2;

public:
    /**
     * @brief Constructs a null line (with zero coordinates).
     */
    constexpr line () noexcept {}

    /**
     * @brief Constructs a line that represents the line between
     *        (@a x1, @a y1) and (@a x2, @a y2).
     */
    constexpr line (unit_type x1
            , unit_type y1
            , unit_type x2
            , unit_type y2) noexcept
        : _p1(x1, y1)
        , _p2(x2, y2)
    {}

    ~line () = default;
    line (line const & rhs) = default;
    line & operator = (line const & rhs) = default;

    /**
     * @return The line's start point.
     */
    constexpr inline point_type p1 () const noexcept
    {
        return _p1;
    }

    /**
     * @return The line's end point.
     */
    constexpr inline point_type p2 () const noexcept
    {
        return _p2;
    }
};

#ifdef PFS_GRIOTTE_SOURCE

#endif

}} // namespace pfs::griotte

