////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.16 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "casting.hpp"
#include "griotte/rectangle.hpp"
#include "RoundedRectangleShape.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace griotte {

template <>
void render<rectangle, sf::RenderTarget> (rectangle & item, sf::RenderTarget & r)
{
    sf::RoundedRectangleShape rr;
    rr.setPosition(item.x(), item.y());
    rr.setSize(sf::Vector2f(item.width(), item.height()));
    rr.setCornersRadius(static_cast<float>(item.radius()));
    rr.setOutlineThickness(item.thickness());
    rr.setFillColor(SFML::cast(item.color()));
    rr.setOutlineColor(SFML::cast(item.outline_color()));

    r.draw(rr);
}

void rectangle::render (sf::RenderTarget * r)
{
    griotte::render(*this, *r);
}

} // namespace griotte::SFML
