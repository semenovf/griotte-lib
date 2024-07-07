////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2020.05.10 Initial version
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace pfs {
namespace griotte {

class glyph
{
    unsigned int _texture_id {0}; // ID handle of the glyph texture
    unsigned int _width {0};      // width as size component of glyph
    unsigned int _height {0};     // height as size component of glyph
    int _bearing_x {0};           // Offset from baseline to left/top of glyph
    int _bearing_y {0};           // Offset from baseline to left/top of glyph
    unsigned int _advance {0};    // Offset to advance to next glyph

public:
    glyph () {}

    glyph (unsigned int texture_id)
        : _texture_id(texture_id)
    {}

    glyph (glyph const & rhs) = default;
    glyph & operator = (glyph const & rhs) = default;
    glyph (glyph && rhs) = default;
    glyph & operator = (glyph && rhs) = default;

    void set_bearings (int bx , int by)
    {
        _bearing_x = bx;
        _bearing_y = by;
    }

    void set_size (unsigned int width, unsigned int height)
    {
        _width = width;
        _height = height;
    }

    unsigned int width () const noexcept
    {
        return _width;
    }

    unsigned int height () const noexcept
    {
        return _height;
    }

    void set_advance (unsigned int advance)
    {
        _advance = advance;
    }

    unsigned int id () const
    {
        return _texture_id;
    }
};

}} // namespace pfs::griotte
