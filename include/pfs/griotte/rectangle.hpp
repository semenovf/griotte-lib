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
#include "item.hpp"
#include "outlined.hpp"

namespace griotte {

class rectangle: public item, public outlined
{
protected:
    unit_t _radius {0};
    color_t _color;

public:
    rectangle (): item () {}
    ~rectangle () = default;

    constexpr unit_t radius () const noexcept
    {
        return _radius;
    }

    void set_radius (unit_t value)
    {
        _radius = value;
    }

    color_t color () const noexcept
    {
        return _color;
    }

    void set_color (color_t value)
    {
        _color = value;
    }

    void render (renderer_ptr_t r) override;
};

} // namespace griotte
