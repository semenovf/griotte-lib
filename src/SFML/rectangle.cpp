////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.16 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "casting.hpp"
#include "rectangle.hpp"
#include "RoundedRectangleShape.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace griotte {

void rectangle::render (sf::RenderTarget * r)
{
    sf::RoundedRectangleShape rr;
    rr.setPosition(x(), y());
    rr.setSize(sf::Vector2f(width(), height()));
    rr.setCornersRadius(static_cast<float>(radius()));
    rr.setOutlineThickness(thickness());
    rr.setFillColor(SFML::cast(color()));
    rr.setOutlineColor(SFML::cast(outline_color()));

    r->draw(rr);
}

} // namespace griotte::SFML
