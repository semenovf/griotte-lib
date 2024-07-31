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

layout::~layout ()
{
    auto node = first_child();

    while (node != nullptr) {
        auto * ptr = static_cast<item *>(node);
        node = next(node);
        delete ptr;
    }
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
