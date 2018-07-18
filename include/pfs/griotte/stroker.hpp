#pragma once
#include <pfs/griotte/point.hpp>
#include <pfs/griotte/path.hpp>
#include <pfs/griotte/pen.hpp>
#include <pfs/griotte/error.hpp>

namespace pfs {
namespace griotte {

template <typename UnitT>
class stroker
{
    using unit_type  = UnitT;
    using path_type  = path<unit_type>;
    using pen_type   = pen<unit_type>;
    using point_type = point<unit_type>;

    path_type * _path;
    point_type  _cp; // current point ((0, 0) by default)

public:
    stroker (path<UnitT> & apath) : _path(& apath) {}

    point_type const & current_point () const
    {
        return _cp;
    }

    template <typename Painter>
    void stroke (Painter & apainter
            , pen<UnitT> const & apen
            , std::error_code & ec) noexcept;

    template <typename Painter>
    void stroke (Painter & apainter, pen<UnitT> const & apen)
    {
        std::error_code ec;
        stroke(apainter, apen, ec);
        if (ec) throw exception(ec);
    }
};

/**
 * @return Last point
 */
template <typename UnitT>
template <typename Painter>
void stroker<UnitT>::stroke (Painter & apainter
        , pen<UnitT> const & apen
        , std::error_code & ec) noexcept
{
    using entry_type = typename path_type::entry;

    if (_path->empty()) {
        ec = make_error_code(errc::success);
        return;
    }

    typename path_type::const_iterator first = _path->cbegin();
    typename path_type::const_iterator last  = _path->cend();

    switch (first->type) {
    case path_entry_enum::move_to:
        _cp = first->p;
        break;
    case path_entry_enum::rel_move_to:
        _cp += first->p;
        break;
    default:
        // Path must be started with 'move_to' or 'rel_move_to' elements
        ec = make_error_code(errc::bad_path);
        return;
    }

    ++first;

    while (first != last) {
        switch (first->type) {
        case path_entry_enum::move_to:
            _cp = first->p;
            break;

        case path_entry_enum::rel_move_to:
            _cp += first->p;
            break;

        case path_entry_enum::line_to: {
            point_type sp = _cp;
            _cp = first->p;
            apainter.draw_line(sp, _cp, apen);
            break;
        }

        case path_entry_enum::rel_line_to: {
            point_type sp = _cp;
            _cp += first->p;
            apainter.draw_line(sp, _cp, apen);
            break;
        }

        case path_entry_enum::hline_to: {
            point_type sp = _cp;
            _cp.set_x(first->p.get_x());
            apainter.draw_line(sp, _cp, apen);
            break;
        }

        case path_entry_enum::rel_hline_to: {
            point_type sp = _cp;
            _cp.increment_x(first->p.get_x());
            apainter.draw_line(sp, _cp, apen);
            break;
        }

        case path_entry_enum::vline_to: {
            point_type sp = _cp;
            _cp.set_y(first->p.get_y());
            apainter.draw_line(sp, _cp, apen);
            break;
        }

        case path_entry_enum::rel_vline_to: {
            point_type sp = _cp;
            _cp.increment_y(first->p.get_y());
            apainter.draw_line(sp, _cp, apen);
            break;
        }

        case path_entry_enum::curve_to: {
            // At least 2 points for curve must be exists in tail of path ...
            if (std::distance(first, last) < 2) {
                ec = make_error_code(errc::bad_path); // incomplete curve
                return;
            }

            // ... and all of them are 'curve_to'
            typename path_type::const_iterator ic1 = first++; // first control point iterator
            typename path_type::const_iterator ic2 = first++; // second control point iterator
            typename path_type::const_iterator iep = first;   // end point iterator

            //
            // ic1->type already equals to 'path_entry_enum::curve_to'
            //
            if (!(ic2->type == path_entry_enum::curve_to
                    && iep->type == path_entry_enum::curve_to)) {
                ec = make_error_code(errc::bad_path); // incomplete curve
                return;
            }

            apainter.draw_curve(_cp
                    , ic1->p
                    , ic2->p
                    , iep->p
                    , apen);
            _cp = iep->p;
            break;
        }

        case path_entry_enum::rel_curve_to: {
            // At least 2 points for curve must be exists in tail of path ...
            if (std::distance(first, last) < 2) {
                ec = make_error_code(errc::bad_path); // incomplete curve
                return;
            }

            // ... and all of them are 'curve_to'
            typename path_type::const_iterator ic1 = first++; // first control point iterator
            typename path_type::const_iterator ic2 = first++; // second control point iterator
            typename path_type::const_iterator iep = first;   // end point iterator

            //
            // ic1->type already equals to 'path_entry_enum::rel_curve_to'
            //
            if (!(ic2->type == path_entry_enum::rel_curve_to
                    && iep->type == path_entry_enum::rel_curve_to)) {
                ec = make_error_code(errc::bad_path); // incomplete curve
                return;
            }

            apainter.draw_curve(_cp
                    , ic1->p + _cp
                    , ic2->p + _cp
                    , iep->p + _cp
                    , apen);

            _cp += iep->p;
            break;
        }

        case path_entry_enum::close_path:
            _cp = first->p;
            break;
        }

        ++first;
    }

    return;
}

}} // namespace pfs::griotte

