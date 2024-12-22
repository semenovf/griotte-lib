////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.30 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "anchors_layout.hpp"
#include "logger.hpp"
#include <pfs/assert.hpp>
#include <pfs/i18n.hpp>

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

anchors_layout::~anchors_layout () = default;

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
    auto valid = rel_spot == anchor_spot::left
        || rel_spot == anchor_spot::right
        || rel_spot == anchor_spot::hcenter;

    if (!valid) {
        logger::e(tr::_("bad anchor for left side"));
        return;
    }

    auto a = retrieve_anchors(& i);
    a->left.rel = & rel;
    a->left.spot = rel_spot;
    a->left.margin = margin;
}

void anchors_layout::set_top (item & i, item & rel, anchor_spot rel_spot, griotte::unit_t margin)
{
    auto valid = rel_spot == anchor_spot::top
        || rel_spot == anchor_spot::bottom
        || rel_spot == anchor_spot::vcenter;

    if (!valid) {
        logger::e(tr::_("bad anchor for top side"));
        return;
    }

    auto a = retrieve_anchors(& i);
    a->top.rel = & rel;
    a->top.spot = rel_spot;
    a->top.margin = margin;
}

void anchors_layout::set_right (item & i, item & rel, anchor_spot rel_spot, griotte::unit_t margin)
{
    auto valid = rel_spot == anchor_spot::left
        || rel_spot == anchor_spot::right
        || rel_spot == anchor_spot::hcenter;

    if (!valid) {
        logger::e(tr::_("bad anchor for right side"));
        return;
    }

    auto a = retrieve_anchors(& i);
    a->right.rel = & rel;
    a->right.spot = rel_spot;
    a->right.margin = margin;
}

void anchors_layout::set_bottom (item & i, item & rel, anchor_spot rel_spot, unit_t margin)
{
    auto valid = rel_spot == anchor_spot::top
        || rel_spot == anchor_spot::bottom
        || rel_spot == anchor_spot::vcenter;

    if (!valid) {
        logger::e(tr::_("bad anchor for bottom side"));
        return;
    }

    auto a = retrieve_anchors(& i);
    a->bottom.rel = & rel;
    a->bottom.spot = rel_spot;
    a->bottom.margin = margin;
}

void anchors_layout::set_hcenter (item & i, item & rel, anchor_spot rel_spot, unit_t offset)
{
    auto valid = rel_spot == anchor_spot::left
        || rel_spot == anchor_spot::right
        || rel_spot == anchor_spot::hcenter;

    if (!valid) {
        logger::e(tr::_("bad anchor for horizontal center"));
        return;
    }

    auto a = retrieve_anchors(& i);
    a->hcenter.rel = & rel;
    a->hcenter.spot = rel_spot;
    a->hcenter.margin = offset;
}

void anchors_layout::set_vcenter (item & i, item & rel, anchor_spot rel_spot, unit_t offset)
{
    auto valid = rel_spot == anchor_spot::top
        || rel_spot == anchor_spot::bottom
        || rel_spot == anchor_spot::vcenter;

    if (!valid) {
        logger::e(tr::_("bad anchor for vertical center"));
        return;
    }

    auto a = retrieve_anchors(& i);
    a->vcenter.rel = & rel;
    a->vcenter.spot = rel_spot;
    a->vcenter.margin = offset;
}

void anchors_layout::set_margins (item & i, griotte::unit_t m)
{
    auto a = retrieve_anchors(& i);
    a->left.margin = a->top.margin = a->right.margin = a->bottom.margin = m;
}

void anchors_layout::center_in (item & i, item & rel)
{
    set_hcenter(i, rel, anchor_spot::hcenter, unit_t{0});
    set_vcenter(i, rel, anchor_spot::vcenter, unit_t{0});
}

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
                case anchor_spot::right:
                    ptr->set_x(a->left.rel->x() + a->left.rel->width() + a->left.margin);
                    break;
                case anchor_spot::hcenter:
                    ptr->set_x(a->left.rel->x() + a->left.rel->width() / 2 + a->left.margin);
                    break;
                default:
                    break;
            }
        }

        if (a->right.rel != nullptr && a->right.spot != anchor_spot::none) {
            switch (a->right.spot) {
                case anchor_spot::left:
                    if (a->width > unit_t{0}) {
                        ptr->set_x(a->right.rel->x() - a->width - a->right.margin);
                        ptr->set_width(a->width);
                    } else {
                        auto w = a->right.rel->x() - ptr->x() - a->right.margin;
                        ptr->set_width(w < 0 ? 0 : w);
                    }
                    break;

                case anchor_spot::right:
                    if (a->width > unit_t{0}) {
                        ptr->set_x(a->right.rel->x() + a->right.rel->width() - a->width - a->right.margin);
                        ptr->set_width(a->width);
                    } else {
                        auto w = a->right.rel->x() + a->right.rel->width() - ptr->x()
                            - a->right.margin;
                        ptr->set_width(w < 0 ? 0 : w);
                    }
                    break;

                case anchor_spot::hcenter:
                    if (a->width > unit_t{0}) {
                        ptr->set_x(a->right.rel->x() + a->right.rel->width() / 2 - a->width - a->right.margin);
                        ptr->set_width(a->width);
                    } else {
                        auto w = a->right.rel->x() + a->right.rel->width() / 2 - ptr->x()
                            - a->right.margin;
                        ptr->set_width(w < 0 ? 0 : w);
                    }
                    break;

                default:
                    break;
            }
        }

        if (a->top.rel != nullptr && a->top.spot != anchor_spot::none) {
            switch (a->top.spot) {
                case anchor_spot::top:
                    ptr->set_y(a->top.rel->y() + a->top.margin);
                    break;
                case anchor_spot::bottom:
                    ptr->set_y(a->top.rel->y() + a->top.rel->height() + a->top.margin);
                    break;
                case anchor_spot::vcenter:
                    ptr->set_y(a->top.rel->y() + a->top.rel->height() / 2 + a->top.margin);
                    break;
                default:
                    break;
            }
        }

        if (a->bottom.rel != nullptr && a->bottom.spot != anchor_spot::none) {
            switch (a->bottom.spot) {
                case anchor_spot::top:
                    if (a->height > unit_t{0}) {
                        ptr->set_y(a->bottom.rel->y() - a->height - a->bottom.margin);
                        ptr->set_height(a->height);
                    } else {
                        auto h = a->bottom.rel->y() - ptr->y() - a->bottom.margin;
                        ptr->set_height(h < 0 ? 0 : h);
                    }
                    break;
                case anchor_spot::bottom:
                    if (a->height > unit_t{0}) {
                        ptr->set_y(a->bottom.rel->y() + a->bottom.rel->height() - a->height - a->bottom.margin);
                        ptr->set_height(a->height);
                    } else {
                        auto h = a->bottom.rel->y() + a->bottom.rel->height()
                            - ptr->y() - a->bottom.margin;
                        ptr->set_height(h < 0 ? 0 : h);
                    }
                    break;
                case anchor_spot::vcenter:
                    if (a->height > unit_t{0}) {
                        ptr->set_y(a->bottom.rel->y() + a->bottom.rel->height() / 2 - a->height - a->bottom.margin);
                        ptr->set_height(a->height);
                    } else {
                        // ptr->set_height(a->bottom.rel->height() - a->bottom.margin);
                        auto h = a->bottom.rel->y() + a->bottom.rel->height() / 2
                            - ptr->y() - a->bottom.margin;
                        ptr->set_height(h < 0 ? 0 : h);
                    }

                    break;
                default:
                    break;
            }
        }

        if (a->hcenter.rel != nullptr && a->hcenter.spot != anchor_spot::none) {
            switch (a->hcenter.spot) {
                case anchor_spot::left:
                    ptr->set_x(a->hcenter.rel->x() - ptr->width() / 2 + a->hcenter.margin);
                    break;
                case anchor_spot::right:
                    // TODO IMPLEMENT
                    break;
                case anchor_spot::hcenter:
                    ptr->set_x(a->hcenter.rel->x() + (a->hcenter.rel->width() - ptr->width()) / 2 + a->hcenter.margin);
                    break;
                default:
                    break;
            }
        }

        if (a->vcenter.rel != nullptr && a->vcenter.spot != anchor_spot::none) {
            switch (a->vcenter.spot) {
                case anchor_spot::top:
                    ptr->set_y(a->vcenter.rel->y() - ptr->height() / 2 + a->vcenter.margin);
                    break;
                case anchor_spot::bottom:
                    // TODO IMPLEMENT
                    break;
                case anchor_spot::vcenter:
                    ptr->set_y(a->vcenter.rel->y() + (a->vcenter.rel->height() - ptr->height()) / 2 + a->vcenter.margin);
                    break;
                default:
                    break;
            }
        }

        node = next(node);
    }
}

} // namespace griotte
