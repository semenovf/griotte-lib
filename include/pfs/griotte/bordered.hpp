////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.07 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "color.hpp"
#include "unit.hpp"

namespace griotte {

class bordered
{
private:
    unit_t _left {0};   /// Left width
    unit_t _top {0};    /// Top width
    unit_t _right {0};  /// Right width
    unit_t _bottom {0}; /// Bottom width
    color_t _color;     /// Border color

public:
    color_t color () const noexcept { return _color; }

    void set_border_width (unit_t width)
    {
        _left = _top = _right = _bottom = width;
    }

    void set_border (unit_t hwidth, unit_t vwidth)
    {
        _left = _right = hwidth;
        _top = _bottom = vwidth;
    }

    void set_border_width (unit_t left, unit_t top, unit_t right, unit_t bottom)
    {
        _left = left;
        _top = top;
        _right = right;
        _bottom = bottom;
    }
};

} // namespace griotte
