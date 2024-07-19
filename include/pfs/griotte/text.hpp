////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.18 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "color.hpp"
#include "font.hpp"
#include "fontstyle.hpp"
#include "item.hpp"
#include <string>

namespace griotte {

class text: public item
{
protected:
    std::string  _value;
    unsigned int _pixel_size {0};
    color_t      _color;
    font_t       _font;
    fontstyle    _font_style;

public:
    text (): item () {}
    text (std::string value)
        : item ()
        , _value(std::move(value))
    {}

    ~text () = default;

    unsigned int pixel_size () const noexcept
    {
        return _pixel_size;
    }

    void set_pixel_size (unsigned int value)
    {
        _pixel_size = value;
    }

    color_t color () const noexcept
    {
        return _color;
    }

    void set_color (color_t value)
    {
        _color = value;
    }

    std::string const & value () const noexcept
    {
        return _value;
    }

    void set_value (std::string value)
    {
        _value = std::move(value);
    }

    font_t font () const noexcept
    {
        return _font;
    }

    void set_font (font_t value)
    {
        _font = value;
    }

    fontstyle font_style () const noexcept
    {
        return _font_style;
    }

    void set_font_style (fontstyle value)
    {
        _font_style = value;
    }

    void render (renderer_ptr_t r) override;
};

} // namespace griotte

