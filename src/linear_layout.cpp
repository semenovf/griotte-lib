////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.12.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "linear_layout.hpp"
// #include "logger.hpp"
#include <pfs/assert.hpp>
// #include <pfs/i18n.hpp>
#include <type_traits>

namespace griotte {

linear_layout::linear_layout (orientation orient)
    : _orient(orient)
{
    static_assert(std::is_trivially_destructible_v<elem>, "");
}

linear_layout::~linear_layout () = default;

inline linear_layout::elem * linear_layout::elem_cast (node * n)
{
    return reinterpret_cast<linear_layout::elem *>(n->pdata());
}

inline linear_layout::elem * linear_layout::elem_cast (item * i)
{
    return elem_cast(static_cast<node *>(i));
}

void linear_layout::set_margins (item & i, unit_t margins[4])
{
    auto p = elem_cast(& i);
    p->margins[0] = margins[0];
    p->margins[1] = margins[1];
    p->margins[2] = margins[2];
    p->margins[3] = margins[3];
}

void linear_layout::set_margins (item & i, unit_t margins)
{
    auto p = elem_cast(& i);
    p->margins[0] = p->margins[1] = p->margins[2] = p->margins[3] = margins;
}

void linear_layout::set_margin (item & i, direction dir, unit_t value)
{
    auto p = elem_cast(& i);
    p->margins[static_cast<int>(dir)] = value;
}

void linear_layout::set_preferred_width (item & i, unit_t w)
{
    auto p = elem_cast(& i);
    p->preferred_width = w;
}

void linear_layout::set_preferred_height (item & i, unit_t h)
{
    auto p = elem_cast(& i);
    p->preferred_height = h;
}

void linear_layout::update ()
{
    unit_t remaining_dim = _orient == orientation::horizontal ? width() : height();
    unit_t dim = remaining_dim  / _count;
    auto counter = _count;
    auto node = last_child();

    while (node != nullptr) {
        auto ptr = static_cast<item *>(node);
        auto el = elem_cast(node);

        if (_orient == orientation::horizontal) {
            if (el->preferred_width >= 0) {
                ptr->set_width(el->preferred_width - el->margins[0] - el->margins[2]);
                remaining_dim -= el->preferred_width + el->margins[0] + el->margins[2];
                counter--;
            } else {
                remaining_dim -= el->margins[0] + el->margins[2];
            }
        } else {
            if (el->preferred_height >= 0) {
                ptr->set_height(el->preferred_height - el->margins[1] - el->margins[3]);
                remaining_dim -= el->preferred_width + el->margins[1] + el->margins[3];
                counter--;
            } else {
                remaining_dim -= el->margins[1] + el->margins[3];
            }
        }

        node = prev(node);
    }

    dim = remaining_dim  / counter;
    counter = _count;
    node = first_child();
    unit_t coord = _orient == orientation::horizontal ? x() : y();

    while (node != nullptr) {
        counter--;
        auto ptr = static_cast<item *>(node);
        auto el = elem_cast(node);

        // if (counter == 0)
        //     dim = remaining_dim;

        if (_orient == orientation::horizontal) {
            coord += el->margins[0];
            ptr->set_x(coord);

            if (el->preferred_width < 0) {
                ptr->set_width(dim - el->margins[0] - el->margins[2]);
            }

            coord += ptr->width() + el->margins[2];

            // FIXME
            ptr->set_y(y() + el->margins[1]);
            ptr->set_height(height() - el->margins[1] - el->margins[3]);
        } else {
            coord += el->margins[1];
            ptr->set_y(coord);

            if (el->preferred_height < 0) {
                ptr->set_height(dim - el->margins[1] - el->margins[3]);
            } else {

            }

            coord += ptr->height() + el->margins[2];

            // FIXME
            ptr->set_x(x() + el->margins[0]);
            ptr->set_width(width() - el->margins[0] - el->margins[2]);
        }

        // remaining_dim -= dim;
        node = next(node);
    }
}

} // namespace griotte

