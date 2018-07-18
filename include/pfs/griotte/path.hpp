#pragma once
#include <cassert>
#include <vector>
#include <pfs/griotte/point.hpp>
#include <pfs/griotte/rect.hpp>


// FIXME Implement path using relative coordinates internally.

//
// [8.3.8 The grammar for path data](https://www.w3.org/TR/SVGTiny12/paths.html#PathElement)
//
//     path-data ::=
//         wsp* moveto-drawto-command-groups? wsp*
//     moveto-drawto-command-groups ::=
//         moveto-drawto-command-group
//         | moveto-drawto-command-group wsp* moveto-drawto-command-groups
//     moveto-drawto-command-group ::=
//         moveto wsp* drawto-commands?
//     drawto-commands ::=
//         drawto-command
//         | drawto-command wsp* drawto-commands
//     drawto-command ::=
//         closepath
//         | lineto
//         | horizontal-lineto
//         | vertical-lineto
//         | curveto
//         | smooth-curveto
//         | quadratic-bezier-curveto
//         | smooth-quadratic-bezier-curveto
//     moveto ::=
//         ( "M" | "m" ) wsp* moveto-argument-sequence
//     moveto-argument-sequence ::=
//         coordinate-pair
//         | coordinate-pair comma-wsp? lineto-argument-sequence
//     closepath ::=
//         ("Z" | "z")
//     lineto ::=
//         ( "L" | "l" ) wsp* lineto-argument-sequence
//     lineto-argument-sequence ::=
//         coordinate-pair
//         | coordinate-pair comma-wsp? lineto-argument-sequence
//     horizontal-lineto ::=
//         ( "H" | "h" ) wsp* horizontal-lineto-argument-sequence
//     horizontal-lineto-argument-sequence ::=
//         coordinate
//         | coordinate comma-wsp? horizontal-lineto-argument-sequence
//     vertical-lineto ::=
//         ( "V" | "v" ) wsp* vertical-lineto-argument-sequence
//     vertical-lineto-argument-sequence ::=
//         coordinate
//         | coordinate comma-wsp? vertical-lineto-argument-sequence
//     curveto ::=
//         ( "C" | "c" ) wsp* curveto-argument-sequence
//     curveto-argument-sequence ::=
//         curveto-argument
//         | curveto-argument comma-wsp? curveto-argument-sequence
//     curveto-argument ::=
//         coordinate-pair comma-wsp? coordinate-pair comma-wsp? coordinate-pair
//     smooth-curveto ::=
//         ( "S" | "s" ) wsp* smooth-curveto-argument-sequence
//     smooth-curveto-argument-sequence ::=
//         smooth-curveto-argument
//         | smooth-curveto-argument comma-wsp? smooth-curveto-argument-sequence
//     smooth-curveto-argument ::=
//         coordinate-pair comma-wsp? coordinate-pair
//     quadratic-bezier-curveto ::=
//         ( "Q" | "q" ) wsp* quadratic-bezier-curveto-argument-sequence
//     quadratic-bezier-curveto-argument-sequence ::=
//         quadratic-bezier-curveto-argument
//         | quadratic-bezier-curveto-argument comma-wsp?
//             quadratic-bezier-curveto-argument-sequence
//     quadratic-bezier-curveto-argument ::=
//         coordinate-pair comma-wsp? coordinate-pair
//     smooth-quadratic-bezier-curveto ::=
//         ( "T" | "t" ) wsp* smooth-quadratic-bezier-curveto-argument-sequence
//     smooth-quadratic-bezier-curveto-argument-sequence ::=
//         coordinate-pair
//         | coordinate-pair comma-wsp? smooth-quadratic-bezier-curveto-argument-sequence
//     coordinate-pair ::=
//         coordinate comma-wsp? coordinate
//     coordinate ::=
//         number
//     nonnegative-number ::=
//         integer-constant
//         | floating-point-constant
//     number ::=
//         sign? integer-constant
//         | sign? floating-point-constant
//     flag ::=
//         "0" | "1"
//     comma-wsp ::=
//         (wsp+ comma? wsp*) | (comma wsp*)
//     comma ::=
//         ","
//     integer-constant ::=
//         digit-sequence
//     floating-point-constant ::=
//         fractional-constant exponent?
//         | digit-sequence exponent
//     fractional-constant ::=
//         digit-sequence? "." digit-sequence
//         | digit-sequence "."
//     exponent ::=
//         ( "e" | "E" ) sign? digit-sequence
//     sign ::=
//         "+" | "-"
//     digit-sequence ::=
//         digit
//         | digit digit-sequence
//     digit ::=
//         "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
//     wsp ::=
//         (#x20 | #x9 | #xD | #xA)


namespace pfs {
namespace griotte {

enum class path_entry_enum : int
{
      move_to      ///!<Move to
    , rel_move_to  ///!<Relative move to
    , line_to      ///!<Line to
    , rel_line_to  ///!<Relative line to
    , hline_to     ///!<Horizontal line to
    , rel_hline_to ///!<Relative horizontal line to
    , vline_to     ///!<Vertical line to
    , rel_vline_to ///!<Relative vertical line to
    , curve_to     ///!<Curve to
    , rel_curve_to ///!<Relative curve to
    , close_path   ///!<Close path
};

template <typename UnitT>
class path
{
public:
    using unit_type  = UnitT;
    using point_type = point<unit_type>;
    using rect_type  = rect<unit_type>;

    struct entry
    {
        path_entry_enum type;
        point_type p;

        entry (path_entry_enum atype
                , point_type const & apoint)
            : type{atype}
            , p{apoint}
        {}
    };

    using entry_collection = std::vector<entry>;
    using iterator         = typename entry_collection::iterator;
    using const_iterator   = typename entry_collection::const_iterator;
    using reference        = typename entry_collection::reference;
    using const_reference  = typename entry_collection::const_reference;

private:
    entry_collection _v; // collection of the path antries

public:
    /**
     * @brief Constructs a path with start point at (0, 0).
     */
    path () noexcept
    {
        move_to(point_type{0, 0});
    }

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

    bool empty () const
    {
        return _v.empty();
    }

    iterator begin ()
    {
        return _v.begin();
    }

    iterator end ()
    {
        return _v.end();
    }

    const_iterator begin () const
    {
        return _v.begin();
    }

    const_iterator end () const
    {
        return _v.end();
    }

    const_iterator cbegin () const
    {
        return _v.cbegin();
    }

    const_iterator cend () const
    {
        return _v.cend();
    }

    void move_to (point_type const & apoint, bool is_relative = false);

    inline void move_to (unit_type x, unit_type y, bool is_relative = false)
    {
        move_to(point_type{x, y}, is_relative);
    }

    inline void line_to (point_type const & apoint, bool is_relative = false)
    {
        assert(!_v.empty());
        _v.emplace_back(is_relative
                ? path_entry_enum::rel_line_to
                : path_entry_enum::line_to, apoint);
    }

    inline void line_to (unit_type x, unit_type y, bool is_relative = false)
    {
        line_to(point_type{x, y}, is_relative);
    }

    inline void hline_to (unit_type x, bool is_relative = false)
    {
        assert(!_v.empty());
        _v.emplace_back(is_relative
                ? path_entry_enum::rel_hline_to
                : path_entry_enum::hline_to, point_type(x, 0));
    }

    inline void vline_to (unit_type y, bool is_relative = false)
    {
        assert(!_v.empty());
        _v.emplace_back(is_relative
                ? path_entry_enum::rel_vline_to
                : path_entry_enum::vline_to, point_type(0, y));
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
            , point_type const & end_point
            , bool is_relative = false)
    {
        assert(!_v.empty());
        path_entry_enum pet = is_relative
                ? path_entry_enum::rel_curve_to
                : path_entry_enum::curve_to;

        _v.emplace_back(pet, c1);
        _v.emplace_back(pet, c2);
        _v.emplace_back(pet, end_point);
    }

    inline void cubic_to (unit_type cx1, unit_type cy1
            , unit_type cx2, unit_type cy2
            , unit_type ex, unit_type ey
            , bool is_relative = false)
    {
        cubic_to(point_type{cx1, cy1}
                , point_type{cx2, cy2}
                , point_type{ex, ey}
                , is_relative);
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
            , point_type const & end_point
            , bool is_relative = false)
    {
        cubic_to(c1, c2, end_point, is_relative);
    }

    inline void curve_to (unit_type cx1, unit_type cy1
            , unit_type cx2, unit_type cy2
            , unit_type ex, unit_type ey
            , bool is_relative = false)
    {
        cubic_to(point_type{cx1, cy1}
                , point_type{cx2, cy2}
                , point_type{ex, ey}
                , is_relative);
    }

    /**
     * @brief Adds a quadratic Bezier curve between the current position and
     *        the given @a end_point with the control point specified by @a c.
     * @param c Control point.
     * @param end_point End point.
     */
    void quad_to (point_type const & c
            , point_type const & end_point
            , bool is_relative = false);

    inline void quad_to (unit_type cx, unit_type cy
            , unit_type ex, unit_type ey
            , bool is_relative = false)
    {
        quad_to(point_type{cx, cy}
                , point_type{ex, ey}
                , is_relative);
    }

    void close_path ()
    {
        assert(!_v.empty());
        _v.emplace_back(path_entry_enum::close_path, point_type{0, 0});
    }

    /**
     * @brief Appends the given @a apath to this path as a closed subpath.
     */
    inline void append_path (path const & apath)
    {
        _v.insert(_v.begin(), apath._v.cbegin(), apath._v.cend());
    }

    friend rect_type bounding_rect (path const & apath);
    friend rect_type control_point_rect (path const & apath);
};

template <typename UnitT>
void path<UnitT>::move_to (point_type const & apoint, bool is_relative)
{
    path_entry_enum type = is_relative
                ? path_entry_enum::rel_move_to
                : path_entry_enum::move_to;

    if (_v.empty()) {
        _v.emplace_back(type, apoint);
        return;
    }

    reference back = _v.back();

    if (!(back.type == path_entry_enum::move_to
            || back.type == path_entry_enum::rel_move_to)) {
        _v.emplace_back(type, apoint);
        return;
    }

    //
    // There are four variants:
    // 1. M x1 y1 M x2 y2
    // 2. m x1 y1 M x2 y2
    // 3. M x1 y1 m x2 y2
    // 4. m x1 y1 m x2 y2
    //

    // Variants 1 and 2.
    if (!is_relative) {
        back.p = apoint;
        back.type = path_entry_enum::move_to;
        return;
    }

    // Variants 3 and 4.
    back.p += apoint;
}

template <typename UnitT>
void path<UnitT>::quad_to (point_type const & c
            , point_type const & end_point
            , bool is_relative)
{
    assert(!_v.empty());
    point_type const & start_point = _v.back().p;

    if (start_point == c && c == end_point)
        return;

    point_type c1{(start_point.get_x() + 2 * c.get_x()) / 3
            , (start_point.get_y() + 2 * c.get_y()) / 3};

    point_type c2{(end_point.get_x() + 2 * c.get_x()) / 3
        , (end_point.get_y() + 2 * c.get_y()) / 3};

    cubic_to(c1, c2, end_point, is_relative);
}

/**
 * @return Calculated bounding rectangle of painter path @a apath.
 */
template <typename UnitT>
rect<UnitT> bounding_rect (path<UnitT> const & apath)
{
    using rect_type = rect<UnitT>;
    rect_type r;

    // TODO Implement bounding_rect()
    // // see qt5/qtbase/src/gui/painting/qpainterpath.cpp:computeBoundingRect()

    return r;
}

/**
 * @return Calculated rectangle containing all the points and
 *         control points in path @a apath.
 * @note This function is significantly faster to compute than the exact
 *        bounding_rect(), and the returned rectangle is always a superset
 *        of the rectangle returned by bounding_rect().
 */
template <typename UnitT>
rect<UnitT> control_point_rect (path<UnitT> const & apath)
{
    using rect_type = rect<UnitT>;
    rect_type r;

    // TODO Implement control_point_rect()
    // see qt5/qtbase/src/gui/painting/qpainterpath.cpp:computeControlPointRect()

    return r;
}


}} // namespace pfs::griotte
