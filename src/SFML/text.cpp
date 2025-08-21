////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "casting.hpp"
#include "logger.hpp"
#include "RoundedRectangleShape.hpp"
#include "griotte/text.hpp"
#include <pfs/i18n.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <pfs/log.hpp>

namespace griotte {

extern sf::Font const & native_font (font_t const & f);

text_t::text_t () = default;

text_t::text_t (std::string s)
    : content(std::move(s))
{}

text_t::~text_t () = default;

static void populate (text_t const * src, sf::Text * target)
{
    target->setString(SFML::cast(src->content));
    target->setCharacterSize(src->pixel_size); // in pixels, not points!
    target->setFillColor(SFML::cast(src->color));
    target->setFont(native_font(src->font));

    // Configure and set font style
    sf::Uint32 sf_font_style = sf::Text::Regular;

    if (src->font_style.is_bold())
        sf_font_style |= sf::Text::Bold;

    if (src->font_style.is_italic())
        sf_font_style |= sf::Text::Italic;

    if (src->font_style.is_underlined())
        sf_font_style |= sf::Text::Underlined;

    if (src->font_style.is_strikeout())
        sf_font_style |= sf::Text::StrikeThrough;

    target->setStyle(sf_font_style);

    sf::FloatRect bounds = target->getGlobalBounds();
    auto geom = src->geometry();

    target->setPosition(geom.x - bounds.left, geom.y - bounds.top);
}

geom2d text_t::bounding_geom () const
{
    sf::Text text;
    populate(this, & text);
    sf::FloatRect bounds = text.getGlobalBounds();
    return geom2d { _geom.x, _geom.y, bounds.width, bounds.height };
}

rect2d text_t::bounding_rect () const
{
    sf::Text text;
    populate(this, & text);
    sf::FloatRect bounds = text.getGlobalBounds();
    return rect2d { _geom.x, _geom.y, _geom.x + bounds.width, _geom.y + bounds.height };
}

void text_t::render (sf::RenderTarget * r)
{
    sf::Text text;
    populate(this, & text);
    r->draw(text);
}

} // namespace griotte::SFML
