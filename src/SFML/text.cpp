////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "casting.hpp"
#include "griotte/logger.hpp"
#include "griotte/text.hpp"
#include "griotte/SFML/font.hpp"
#include "RoundedRectangleShape.hpp"
#include <pfs/i18n.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace griotte {

template <>
void render<text, sf::RenderTarget> (text & item, sf::RenderTarget & r)
{
    sf::Text t;

    auto font = item.font();

    if (!font) {
        logger::e(tr::_("text rendering failure: font not set"));
        return;
    }

    t.setPosition(item.x(), item.y());

    t.setFont(*font);
    t.setString(SFML::cast(item.value()));
    t.setCharacterSize(item.pixel_size()); // in pixels, not points!
    t.setFillColor(SFML::cast(item.color()));

    auto font_style = item.font_style();
    sf::Uint32 style = sf::Text::Regular;

    if (font_style.is_bold())
        style |= sf::Text::Bold;

    if (font_style.is_italic())
        style |= sf::Text::Italic;

    if (font_style.is_underlined())
        style |= sf::Text::Underlined;

    if (font_style.is_strikeout())
        style |= sf::Text::StrikeThrough;

    t.setStyle(style);

    r.draw(t);
}

void text::render (sf::RenderTarget * r)
{
    griotte::render(*this, *r);
}

} // namespace griotte::SFML

