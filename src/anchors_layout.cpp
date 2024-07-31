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

void anchors_layout::set_margins(item & i, griotte::unit_t m)
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

        if (a->left.spot != anchor_spot::none) {
            if (a->left.rel != nullptr) {
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
        }

        if (a->top.spot != anchor_spot::none) {
            if (a->top.rel != nullptr) {
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
        }

        if (a->right.spot != anchor_spot::none) {
            if (a->right.rel != nullptr)
                ptr->set_width(a->right.rel->width() - a->right.margin - a->right.margin);
        }

        if (a->bottom.spot != anchor_spot::none) {
            if (a->bottom.rel != nullptr)
                ptr->set_height(a->bottom.rel->height() - a->bottom.margin- a->bottom.margin);
        }

        node = next(node);
    }
}

} // namespace griotte
