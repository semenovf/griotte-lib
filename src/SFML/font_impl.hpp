////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.12.22 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "griotte/font.hpp"
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>

namespace griotte {

class font::impl: public sf::Font
{
public: // static
    static std::unordered_map<std::string, std::unique_ptr<impl>> s_fonts;
    static impl * s_fallback_font;

public: // static
    static bool add (std::string const & alias, std::unique_ptr<impl> && f, bool is_fallback);
};

} // namespace griotte

