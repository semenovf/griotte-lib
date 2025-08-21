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
#include "font_style.hpp"
#include "item.hpp"
#include <memory>
#include <string>

namespace griotte {

class text_t: public item
{
public:
    std::string content;
    unsigned int pixel_size {12};
    color_t color {78, 78, 78, 255};
    font_t font;
    font_style_t font_style;

public:
    text_t ();
    explicit text_t (std::string content);
    virtual ~text_t ();

    geom2d bounding_geom () const;
    rect2d bounding_rect () const;

    void render (renderer_ptr_t r) override;
};

} // namespace griotte
