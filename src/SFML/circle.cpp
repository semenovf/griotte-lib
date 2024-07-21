////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "casting.hpp"
#include "griotte/circle.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace griotte {

template <>
void render<circle, sf::RenderTarget> (circle & item, sf::RenderTarget & r)
{
    sf::CircleShape c;
    c.setPosition(item.x(), item.y());
    c.setRadius(item.radius());
    c.setOutlineThickness(item.thickness());
    c.setFillColor(SFML::cast(item.color()));
    c.setOutlineColor(SFML::cast(item.outline_color()));

    // Make the circle smoother
    c.setPointCount(static_cast<std::size_t>(item.radius()) / 2);

    r.draw(c);
}

void circle::render (sf::RenderTarget * r)
{
    griotte::render(*this, *r);
}

} // namespace griotte


