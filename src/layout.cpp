////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.16 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "griotte/layout.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace griotte {

void layout::render (sf::RenderTarget * r)
{
    auto node = first_child();

    while (node != nullptr) {
        static_cast<item *>(node)->render(r);
        node = next(node);
    }
}

} // namespace griotte::SFML
