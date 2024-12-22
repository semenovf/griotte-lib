////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.16 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "layout.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace griotte {

layout::layout ()
    : item ()
{
    _margins[0] = _margins[1] = _margins[2] = _margins[3] = 0;
}

layout::~layout ()
{
    auto node = first_child();

    while (node != nullptr) {
        if (node->pdata() != nullptr) {
            auto curr_node = node;
            node = next(node);
            auto ptr = static_cast<item *>(curr_node);

            // This call avoids the node from being destroyed again by the parent destructor.
            remove_child(curr_node);

            ptr->~item();

            auto raw = reinterpret_cast<char *>(curr_node->pdata());
            delete [] raw;
        } else {
            auto * ptr = static_cast<item *>(node);
            node = next(node);
            delete ptr;
        }
    }
}

void layout::set_margins (unit_t margins[4])
{
    _margins[0] = margins[0];
    _margins[1] = margins[1];
    _margins[2] = margins[2];
    _margins[3] = margins[3];
}

void layout::set_margin (direction dir, unit_t value)
{
    _margins[static_cast<int>(dir)] = value;
}

void layout::render (sf::RenderTarget * r)
{
    auto node = first_child();

    while (node != nullptr) {
        static_cast<item *>(node)->render(r);
        node = next(node);
    }
}

} // namespace griotte::SFML
