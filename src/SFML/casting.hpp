////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.13 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "color.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>
#include <cstring>

namespace griotte {
namespace SFML {

inline sf::String cast (std::string const & utf8)
{
    return sf::String::fromUtf8(utf8.begin(), utf8.end());
}

inline sf::String cast (char const * utf8)
{
    return sf::String::fromUtf8(utf8, utf8 + std::strlen(utf8));
}

inline std::string cast (sf::String const & s)
{
    // See String::toUtf8() implementation

    // Prepare the output string
    std::string output;
    output.reserve(s.getSize() * 2);

    // Convert
    sf::Utf32::toUtf8(s.begin(), s.end(), std::back_inserter(output));

    return output;

}

inline sf::Color cast (rgba_color const & c)
{
    return sf::Color{c.red(), c.green(), c.blue(), c.alpha()};
}

inline rgba_color cast_rgba (sf::Color const & c)
{
    return rgba_color{c.r, c.g, c.b, c.a};
}

}} // namespace griotte::SFML
