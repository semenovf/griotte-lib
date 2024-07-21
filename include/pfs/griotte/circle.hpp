////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "color.hpp"
#include "item.hpp"
#include "outlined.hpp"

namespace griotte {

class circle: public item, public outlined
{
protected:
    // unit_t _radius {0};
    color_t _color;

public:
    circle (): item () {}
    ~circle () = default;

    /**
     * Circle radius.
     */
    unit_t radius () const noexcept;

    /**
     * Set circle radius.
     */
    void set_radius (unit_t value);

    color_t color () const noexcept
    {
        return _color;
    }

    void set_color (color_t value)
    {
        _color = value;
    }

    /**
     * Origin (center) of the circle.
     */
    point_t origin () const noexcept;

    /**
     * Set origin (center) of the circle.
     */
    void set_origin (unit_t x, unit_t y);

    /**
     * Set origin (center) of the circle.
     */
    void set_origin (point_t p)
    {
        set_origin(p.x, p.y);
    }

    void render (renderer_ptr_t r) override;
};

} // namespace griotte

