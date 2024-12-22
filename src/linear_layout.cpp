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

namespace griotte {

// inline anchors * retrieve_anchors (node * n)
// {
//     auto raw = reinterpret_cast<char *>(n->pdata());
//     return reinterpret_cast<anchors *>(raw);
// }
//
// inline anchors * retrieve_anchors (item * i)
// {
//     auto n = static_cast<node *>(i);
//     return retrieve_anchors(n);
// }

linear_layout::linear_layout (orientation orient)
    : _orient(orient)
{}

linear_layout::~linear_layout () = default;


// void anchors_layout::set_width (item & i, unit_t w)
// {
//     auto a = retrieve_anchors(& i);
//     i.set_width(w);
//     a->width = w;
// }
//
// void anchors_layout::set_height (item & i, unit_t h)
// {
//     auto a = retrieve_anchors(& i);
//     i.set_height(h);
//     a->height = h;
// }
//
// void anchors_layout::fill (item & i, item & rel)
// {
//     auto a = retrieve_anchors(& i);
//
//     a->left.rel = a->top.rel = a->right.rel = a->bottom.rel = & rel;
//     a->left.spot   = anchor_spot::left;
//     a->top.spot    = anchor_spot::top;
//     a->right.spot  = anchor_spot::right;
//     a->bottom.spot = anchor_spot::bottom;
// }
//
// void anchors_layout::set_left (item & i, item & rel, anchor_spot rel_spot, griotte::unit_t margin)
// {
//     auto valid = rel_spot == anchor_spot::left
//         || rel_spot == anchor_spot::right
//         || rel_spot == anchor_spot::hcenter;
//
//     if (!valid) {
//         logger::e(tr::_("bad anchor for left side"));
//         return;
//     }
//
//     auto a = retrieve_anchors(& i);
//     a->left.rel = & rel;
//     a->left.spot = rel_spot;
//     a->left.margin = margin;
// }
//
// void anchors_layout::set_top (item & i, item & rel, anchor_spot rel_spot, griotte::unit_t margin)
// {
//     auto valid = rel_spot == anchor_spot::top
//         || rel_spot == anchor_spot::bottom
//         || rel_spot == anchor_spot::vcenter;
//
//     if (!valid) {
//         logger::e(tr::_("bad anchor for top side"));
//         return;
//     }
//
//     auto a = retrieve_anchors(& i);
//     a->top.rel = & rel;
//     a->top.spot = rel_spot;
//     a->top.margin = margin;
// }
//
// void anchors_layout::set_right (item & i, item & rel, anchor_spot rel_spot, griotte::unit_t margin)
// {
//     auto valid = rel_spot == anchor_spot::left
//         || rel_spot == anchor_spot::right
//         || rel_spot == anchor_spot::hcenter;
//
//     if (!valid) {
//         logger::e(tr::_("bad anchor for right side"));
//         return;
//     }
//
//     auto a = retrieve_anchors(& i);
//     a->right.rel = & rel;
//     a->right.spot = rel_spot;
//     a->right.margin = margin;
// }
//
// void anchors_layout::set_bottom (item & i, item & rel, anchor_spot rel_spot, unit_t margin)
// {
//     auto valid = rel_spot == anchor_spot::top
//         || rel_spot == anchor_spot::bottom
//         || rel_spot == anchor_spot::vcenter;
//
//     if (!valid) {
//         logger::e(tr::_("bad anchor for bottom side"));
//         return;
//     }
//
//     auto a = retrieve_anchors(& i);
//     a->bottom.rel = & rel;
//     a->bottom.spot = rel_spot;
//     a->bottom.margin = margin;
// }
//
// void anchors_layout::set_hcenter (item & i, item & rel, anchor_spot rel_spot, unit_t offset)
// {
//     auto valid = rel_spot == anchor_spot::left
//         || rel_spot == anchor_spot::right
//         || rel_spot == anchor_spot::hcenter;
//
//     if (!valid) {
//         logger::e(tr::_("bad anchor for horizontal center"));
//         return;
//     }
//
//     auto a = retrieve_anchors(& i);
//     a->hcenter.rel = & rel;
//     a->hcenter.spot = rel_spot;
//     a->hcenter.margin = offset;
// }
//
// void anchors_layout::set_vcenter (item & i, item & rel, anchor_spot rel_spot, unit_t offset)
// {
//     auto valid = rel_spot == anchor_spot::top
//         || rel_spot == anchor_spot::bottom
//         || rel_spot == anchor_spot::vcenter;
//
//     if (!valid) {
//         logger::e(tr::_("bad anchor for vertical center"));
//         return;
//     }
//
//     auto a = retrieve_anchors(& i);
//     a->vcenter.rel = & rel;
//     a->vcenter.spot = rel_spot;
//     a->vcenter.margin = offset;
// }
//
// void anchors_layout::set_margins (item & i, griotte::unit_t m)
// {
//     auto a = retrieve_anchors(& i);
//     a->left.margin = a->top.margin = a->right.margin = a->bottom.margin = m;
// }
//
// void anchors_layout::center_in (item & i, item & rel)
// {
//     set_hcenter(i, rel, anchor_spot::hcenter, unit_t{0});
//     set_vcenter(i, rel, anchor_spot::vcenter, unit_t{0});
// }

void linear_layout::update ()
{
    auto node = first_child();

    while (node != nullptr) {
        auto ptr = static_cast<item *>(node);

        // TODO Implement linear layout

        node = next(node);
    }
}

} // namespace griotte

