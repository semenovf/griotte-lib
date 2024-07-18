////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.13 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "griotte/color.hpp"
#include <SFML/Graphics/Color.hpp>

namespace griotte {
namespace SFML {

inline sf::Color cast (rgba_color const & c)
{
    return sf::Color{c.red(), c.green(), c.blue(), c.alpha()};
}

inline rgba_color cast_rgba (sf::Color const & c)
{
    return rgba_color{c.r, c.g, c.b, c.a};
}

}} // namespace griotte::SFML
