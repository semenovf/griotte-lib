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

class outlined
{
private:
    unit_t _thickness {0};
    color_t _color;

public:
    unit_t thickness () const noexcept
    {
        return _thickness;
    }

    color_t outline_color () const noexcept
    {
        return _color;
    }

    void set_thickness (unit_t value)
    {
        _thickness = value;
    }

    void set_outline_color (color_t value)
    {
        _color = value;
    }
};

} // namespace griotte
