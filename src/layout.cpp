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
    _paddings[0] = _paddings[1] = _paddings[2] = _paddings[3] = 0;
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

void layout::set_paddings (unit_t paddings[4])
{
    _paddings[0] = paddings[0];
    _paddings[1] = paddings[1];
    _paddings[2] = paddings[2];
    _paddings[3] = paddings[3];
}

void layout::set_paddings (unit_t paddings)
{
    _paddings[0] = _paddings[1] = _paddings[2] = _paddings[3] = paddings;
}

void layout::set_padding (direction dir, unit_t value)
{
    _paddings[static_cast<int>(dir)] = value;
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
