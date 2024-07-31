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
#include <pfs/optional.hpp>
#include <string>

namespace griotte {

template <typename Rep>
class text: public item
{
protected:
    Rep _rep;
    font_t _font;
    fontstyle _font_style;
    pfs::optional<color_t> _bgcolor;

public:
    text ();
    text (std::string const & value);
    ~text ();

    unsigned int pixel_size () const noexcept;
    void set_pixel_size (unsigned int value);

    color_t color () const noexcept;
    void set_color (color_t value);

    std::string string () const noexcept;
    void set_string (std::string const & string);

    font_t font () const noexcept
    {
        return _font;
    }

    void set_font (font_t f);

    fontstyle font_style () const noexcept
    {
        return _font_style;
    }

    void set_font_style (fontstyle value);

    void set_bgcolor (color_t value)
    {
        _bgcolor = value;
    }

    void clear_bgcolor ()
    {
        _bgcolor = pfs::nullopt;
    }

    pfs::optional<color_t> bgcolor () const noexcept
    {
        return _bgcolor;
    }

    geom2d bounding_geom () const;
    rect2d bounding_rect () const;

    void set_position (unit_t x, unit_t y) override;

    void render (renderer_ptr_t r) override;
};

} // namespace griotte
