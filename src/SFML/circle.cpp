////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "casting.hpp"
#include "circle.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace griotte {

void circle::render (sf::RenderTarget * r)
{
    sf::CircleShape c;
    c.setPosition(x(), y());
    c.setRadius(radius());
    c.setOutlineThickness(thickness());
    c.setFillColor(SFML::cast(color()));
    c.setOutlineColor(SFML::cast(outline_color()));

    // Make the circle smoother
    //c.setPointCount(static_cast<std::size_t>(radius()) / 2);
    c.setPointCount(static_cast<std::size_t>(radius()));

    r->draw(c);
}

} // namespace griotte
