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
#include "font_impl.hpp"
#include "RoundedRectangleShape.hpp"
#include "griotte/text.hpp"
#include <pfs/i18n.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <pfs/log.hpp>

namespace griotte {

class text::impl
{
public:
    sf::Text text;
};

text::text ()
    : item ()
    , _d(new impl)
{}

text::text (std::string const & string)
    : item ()
    , _d(new impl)
{
    _d->text.setString(SFML::cast(string));
}

text::~text () = default;

unsigned int text::pixel_size () const noexcept
{
    return _d->text.getCharacterSize();
}

void text::set_pixel_size (unsigned int value)
{
    _d->text.setCharacterSize(value); // in pixels, not points!
}

color_t text::color () const noexcept
{
    return SFML::cast_rgba(_d->text.getFillColor());
}

void text::set_color (color_t value)
{
    _d->text.setFillColor(SFML::cast(value));
}

std::string text::string () const noexcept
{
    return SFML::cast(_d->text.getString());
}

void text::set_string (std::string const & value)
{
    _d->text.setString(SFML::cast(value));
}

void text::set_font (font f)
{
    _font = f;
    auto ptr = _font.native();

    if (ptr != nullptr)
        _d->text.setFont(*static_cast<sf::Font *>(ptr));
}

void text::set_font_style (fontstyle fstyle)
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

    _d->text.setStyle(sf_font_style);
}

geom2d text::bounding_geom () const
{
    sf::FloatRect bounds = _d->text.getGlobalBounds();
    return geom2d { _geom.x, _geom.y, bounds.width, bounds.height };
}

rect2d text::bounding_rect () const
{
    sf::FloatRect bounds = _d->text.getGlobalBounds();
    return rect2d { _geom.x, _geom.y, bounds.width, bounds.height };
}

void text::set_position (unit_t x, unit_t y)
{
    item::set_position(x, y);
    sf::FloatRect bounds = _d->text.getGlobalBounds();
    _d->text.setPosition(_geom.x - bounds.left, _geom.y - bounds.top);
}

void text::render (sf::RenderTarget * r)
{
    if (_bgcolor) {
        sf::RectangleShape rr;
        sf::FloatRect bounds = _d->text.getGlobalBounds();
        rr.setPosition(_geom.x, _geom.y);
        rr.setSize(sf::Vector2f(bounds.width, bounds.height));
        rr.setFillColor(SFML::cast(*_bgcolor));
        r->draw(rr);
    }

    r->draw(_d->text);
}

} // namespace griotte::SFML
