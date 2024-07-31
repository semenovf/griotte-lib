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
#include "SFML/font.hpp"
#include "SFML/text.hpp"
#include "RoundedRectangleShape.hpp"
#include <pfs/i18n.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <pfs/log.hpp>

namespace griotte {

using rep_t = SFML::text_rep;

template <>
text<rep_t>::text (): item () {}

template <>
text<rep_t>::text (std::string const & string)
    : item ()
{
    _rep.d.setString(SFML::cast(string));
}

template <>
text<rep_t>::~text () = default;

template <>
unsigned int text<rep_t>::pixel_size () const noexcept
{
    return _rep.d.getCharacterSize();
}

template <>
void text<rep_t>::set_pixel_size (unsigned int value)
{
    _rep.d.setCharacterSize(value); // in pixels, not points!
}

template <>
color_t text<rep_t>::color () const noexcept
{
    return SFML::cast_rgba(_rep.d.getFillColor());
}

template <>
void text<rep_t>::set_color (color_t value)
{
    _rep.d.setFillColor(SFML::cast(value));
}

template <>
std::string text<rep_t>::string () const noexcept
{
    return SFML::cast(_rep.d.getString());
}

template <>
void text<rep_t>::set_string (std::string const & value)
{
    _rep.d.setString(SFML::cast(value));
}

template <>
void text<rep_t>::set_font (font_t f)
{
    _font = f;
    _rep.d.setFont(*_font);
}

template <>
void text<rep_t>::set_font_style (fontstyle fstyle)
{
    _font_style = fstyle;

    sf::Uint32 sf_font_style = sf::Text::Regular;

    if (_font_style.is_bold())
        sf_font_style |= sf::Text::Bold;

    if (_font_style.is_italic())
        sf_font_style |= sf::Text::Italic;

    if (_font_style.is_underlined())
        sf_font_style |= sf::Text::Underlined;

    if (_font_style.is_strikeout())
        sf_font_style |= sf::Text::StrikeThrough;

    _rep.d.setStyle(sf_font_style);
}

template <>
geom2d text<rep_t>::bounding_geom () const
{
    sf::FloatRect bounds = _rep.d.getGlobalBounds();
    return geom2d { _x, _y, bounds.width, bounds.height };
}

template <>
rect2d text<rep_t>::bounding_rect () const
{
    sf::FloatRect bounds = _rep.d.getGlobalBounds();
    return rect2d { _x, _y, bounds.width, bounds.height };
}

template <>
void text<rep_t>::set_position (unit_t x, unit_t y)
{
    item::set_position(x, y);
    sf::FloatRect bounds = _rep.d.getGlobalBounds();
    _rep.d.setPosition(_x - bounds.left, _y - bounds.top);
}

template <>
void text<rep_t>::render (sf::RenderTarget * r)
{
    if (_bgcolor) {
        sf::RectangleShape rr;
        sf::FloatRect bounds = _rep.d.getGlobalBounds();
        rr.setPosition(_x, _y);
        rr.setSize(sf::Vector2f(bounds.width, bounds.height));
        rr.setFillColor(SFML::cast(*_bgcolor));
        r->draw(rr);
    }

    r->draw(_rep.d);
}

} // namespace griotte::SFML
