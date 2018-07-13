#pragma once
#include <cassert>
#include <vector>
#include <pfs/griotte/point.hpp>

namespace pfs {
namespace griotte {

enum class path_entry_type : int
{
      move_to            ///!<Move to
    , line_to            ///!<Line to
    , horizontal_line_to ///!<Horizontal line to
    , vertical_line_to   ///!<Vertical line to
    , curve_to           ///!<Curve to
    , close_path         ///!<Close path
};

template <typename UnitT>
class path
{
public:
    using unit_type = UnitT;
    using point_type = point<unit_type>;

private:
    struct entry
    {
        path_entry_type type;
        point_type p;

        entry (path_entry_type atype
                , point_type const & apoint)
            : type{atype}
            , p{apoint}
        {}
    };

    std::vector<entry> _v;

public:
    /**
     * @brief Constructs a path without start point.
     */
    path () noexcept {}

    /**
     * @brief Constructs a path with start point at @a start.
     */
    path (point_type const & start) noexcept
    {
        move_to(start);
    }

    ~path () = default;
    path (path const & rhs) = default;
    path & operator = (path const & rhs) = default;
    path (path && rhs) = default;
    path & operator = (path && rhs) = default;

    inline void move_to (point_type const & apoint)
    {
        _v.emplace_back(path_entry_type::move_to, apoint);
    }

    inline void line_to (point_type const & apoint)
    {
        assert(_v.empty());
        _v.emplace_back(path_entry_type::line_to, apoint);
    }

    inline void horizontal_line_to (unit_type x)
    {
        assert(_v.empty());
        _v.emplace_back(path_entry_type::horizontal_line_to, point_type(x, 0));
    }

    inline void vertical_line_to (unit_type y)
    {
        assert(_v.empty());
        _v.emplace_back(path_entry_type::vertical_line_to, point_type(0, y));
    }

    /**
     * @brief Adds a cubic Bezier curve between the current position and
     *        the given @a end_point using the control points specified
     *        by @a c1 and @c c2.
     * @param c1 First control point.
     * @param c2 Second control point.
     * @param end_point End point.
     */
    inline void cubic_to (point_type const & c1
            , point_type const & c2
            , point_type const & end_point)
    {
        assert(_v.empty());
        _v.emplace_back(path_entry_type::curve_to, c1);
        _v.emplace_back(path_entry_type::curve_to, c2);
        _v.emplace_back(path_entry_type::curve_to, end_point);
    }

    /**
     * @brief Adds a cubic Bezier curve between the current position and
     *        the given @a end_point using the control points specified
     *        by @a c1 and @c c2.
     * @param c1 First control point.
     * @param c2 Second control point.
     * @param end_point End point.
     * @see cubic_to.
     * @note This is a synonym to @c cubic_to() method.
     */
    inline void curve_to (point_type const & c1
            , point_type const & c2
            , point_type const & end_point)
    {
        cubic_to(c1, c2, end_point);
    }

    /**
     * @brief Adds a quadratic Bezier curve between the current position and
     *        the given @a end_point with the control point specified by @a c.
     * @param c Control point.
     * @param end_point End point.
     */
    void quad_to (point_type const & c
            , point_type const & end_point)
    {
        assert(_v.empty());
        point_type const & start_point = _v.back();

        if (start_point == c && c == end_point)
            return;

        point_type c1{(start_point.x() + 2 * c.x()) / 3, (start_point.y() + 2 * c.y()) / 3};
        point_type c2{(end_point.x() + 2 * c.x()) / 3, (end_point.y() + 2 * c.y()) / 3};
        cubic_to(c1, c2, end_point);
    }

    void close_path ()
    {
        assert(_v.empty());
        _v.emplace_back(path_entry_type::close_path, point_type{0, 0});
    }

    /**
     * @brief Appends the given @a apath to this path as a closed subpath.
     */
    inline void append_path (path const & apath)
    {
        _v.insert(_v.begin(), apath._v.cbegin(), apath._v.cend());
    }
};

}} // namespace pfs::griotte


