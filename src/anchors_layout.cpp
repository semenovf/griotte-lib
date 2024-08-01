////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.30 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "anchors_layout.hpp"
#include <pfs/assert.hpp>

#include <pfs/log.hpp>

namespace griotte {

inline anchors * retrieve_anchors (node * n)
{
    auto raw = reinterpret_cast<char *>(n->pdata());
    return reinterpret_cast<anchors *>(raw);
}

inline anchors * retrieve_anchors (item * i)
{
    auto n = static_cast<node *>(i);
    return retrieve_anchors(n);
}

anchors_layout::~anchors_layout ()
{
    auto node = first_child();

    while (node != nullptr) {
        PFS__TERMINATE(node->pdata() != nullptr, "");
        auto curr_node = node;
        node = next(node);
        auto ptr = static_cast<item *>(curr_node);

        // This call avoids the node from being destroyed again by the parent destructor.
        remove_child(curr_node);

        ptr->~item();

        // auto raw = retrieve_begin_raw(curr_node);
        auto raw = reinterpret_cast<char *>(curr_node->pdata());
        delete [] raw;
    }
}

void anchors_layout::set_width (item & i, unit_t w)
{
    auto a = retrieve_anchors(& i);
    i.set_width(w);
    a->width = w;
}

void anchors_layout::set_height (item & i, unit_t h)
{
    auto a = retrieve_anchors(& i);
    i.set_height(h);
    a->height = h;
}

void anchors_layout::fill (item & i, item & rel)
{
    auto a = retrieve_anchors(& i);

    a->left.rel = a->top.rel = a->right.rel = a->bottom.rel = & rel;
    a->left.spot   = anchor_spot::left;
    a->top.spot    = anchor_spot::top;
    a->right.spot  = anchor_spot::right;
    a->bottom.spot = anchor_spot::bottom;
}

void anchors_layout::set_left (item & i, item & rel, anchor_spot rel_spot, griotte::unit_t margin)
{
    auto a = retrieve_anchors(& i);
    a->left.rel = & rel;
    a->left.spot = rel_spot;
    a->left.margin = margin;
}

void anchors_layout::set_top (item & i, item & rel, anchor_spot rel_spot, griotte::unit_t margin)
{
    auto a = retrieve_anchors(& i);
    a->top.rel = & rel;
    a->top.spot = rel_spot;
    a->top.margin = margin;
}

void anchors_layout::set_right (item & i, item & rel, anchor_spot rel_spot, griotte::unit_t margin)
{
    auto a = retrieve_anchors(& i);
    a->right.rel = & rel;
    a->right.spot = rel_spot;
    a->right.margin = margin;
}

void anchors_layout::set_margins (item & i, griotte::unit_t m)
{
    auto a = retrieve_anchors(& i);
    a->left.margin = a->top.margin = a->right.margin = a->bottom.margin = m;
}

// TODO IMPLEMENT
void anchors_layout::update ()
{
    auto node = first_child();

    while (node != nullptr) {
        auto ptr = static_cast<item *>(node);
        auto a = retrieve_anchors(node);

        if (a->left.rel != nullptr && a->left.spot != anchor_spot::none) {
            switch (a->left.spot) {
                case anchor_spot::left:
                    ptr->set_x(a->left.rel->x() + a->left.margin);
                    break;
                case anchor_spot::top:
                    break;
                case anchor_spot::right:
                    break;
                case anchor_spot::bottom:
                    break;
                case anchor_spot::horizontal_center:
                    break;
                case anchor_spot::vertical_center:
                    break;
                default:
                    break;
            }
        }

        if (a->top.rel != nullptr && a->top.spot != anchor_spot::none) {
            switch (a->top.spot) {
                case anchor_spot::left:
                    break;
                case anchor_spot::top:
                    ptr->set_y(a->top.rel->y() + a->top.margin);
                    break;
                case anchor_spot::right:
                    break;
                case anchor_spot::bottom:
                    break;
                case anchor_spot::horizontal_center:
                    break;
                case anchor_spot::vertical_center:
                    break;
                default:
                    break;
            }
        }

        if (a->right.rel != nullptr && a->right.spot != anchor_spot::none) {
            switch (a->right.spot) {
                case anchor_spot::left:
                    break;
                case anchor_spot::top:
                    break;
                case anchor_spot::right:
                    if (a->width > unit_t{0}) {
                        ptr->set_x(a->right.rel->x() + a->right.rel->width() - ptr->width() - a->right.margin);
                        ptr->set_width(a->width);
                    } else {
                        // width - 2 * right_marging
                        ptr->set_width(a->right.rel->width() - a->right.margin - a->right.margin);
                    }
                    break;
                case anchor_spot::bottom:
                    break;
                case anchor_spot::horizontal_center:
                    break;
                case anchor_spot::vertical_center:
                    break;
                default:
                    break;
            }
        }

        if (a->bottom.rel != nullptr && a->bottom.spot != anchor_spot::none) {
            switch (a->bottom.spot) {
                case anchor_spot::left:
                    break;
                case anchor_spot::top:
                    break;
                case anchor_spot::right:
                    break;
                case anchor_spot::bottom:
                    // height - 2 * bottom_marging
                    ptr->set_height(a->bottom.rel->height() - a->bottom.margin - a->bottom.margin);
                    break;
                case anchor_spot::horizontal_center:
                    break;
                case anchor_spot::vertical_center:
                    break;
                default:
                    break;
            }
        }


        node = next(node);
    }
}

} // namespace griotte
