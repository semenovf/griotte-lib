////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.07 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "renderer.hpp"
#include "node.hpp"
#include "unit.hpp"
#include <pfs/optional.hpp>
#include <cstdint>

namespace griotte {

class item: public node
{
protected:
    unit_t _x {0};
    unit_t _y {0};
    unit_t _w {0};
    unit_t _h {0};
    unit_t _level {0};

    /// The item is visible if @c true
    bool _visible {true};

    /// The item receives mouse and keyboard events if @c true.
    bool _enabled {true};

    float _scale_factor_x {1.0f};
    float _scale_factor_y {1.0f};
    float _rotation {0.0f};

public:
    item () = default;
    virtual ~item () = default;

    constexpr unit_t x () const noexcept { return _x; }
    constexpr unit_t y () const noexcept { return _y; }
    constexpr unit_t level () const noexcept { return _level; }
    constexpr unit_t width () const noexcept { return _w; }
    constexpr unit_t height () const noexcept { return _h; }
    constexpr bool visible () const noexcept { return _visible; }
    constexpr bool enabled () const noexcept { return _enabled; }

    virtual void set_position (unit_t x, unit_t y)
    {
        _x = x;
        _y = y;
    }

    void set_x (unit_t value)
    {
        set_position(value, _y);
    }

    void set_y (unit_t value)
    {
        set_position(_x, value);
    }

    void set_level (unit_t value) { _level = value; }
    void set_width (unit_t value) { _w = value; }
    void set_height (unit_t value) { _h = value; }
    void set_visible (bool value) { _visible = value; }
    void set_enabled (bool value) { _enabled = value; }

    geom_t geometry () const noexcept
    {
        return geom_t {_x, _y, _w, _h};
    }

    void set_geometry (geom_t const & g)
    {
        set_position(g.x, g.y);

        _w = g.w;
        _h = g.h;
    }

    dim_t dimension () const noexcept
    {
        return dim_t{_w, _h};
    }

    void set_scale (float factor_x, float factor_y)
    {
        _scale_factor_x = factor_x;
        _scale_factor_y = factor_y;

        // FIXME See `set_position_callback` usage
    }

    void set_scale (float factor)
    {
        set_scale(factor, factor);
    }

    virtual void render (renderer_ptr_t r) = 0;
};

} // namespace griotte
