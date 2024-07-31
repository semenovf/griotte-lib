////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.27 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <pfs/griotte/text.hpp>
#include <SFML/Graphics/Text.hpp>

namespace griotte {
namespace SFML {

struct text_rep
{
    sf::Text d;
};

}} // namespace griotte::SFML

namespace griotte {

using text_t = text<SFML::text_rep>;

} // namespace griotte
