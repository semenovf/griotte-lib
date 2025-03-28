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
    geom_t _geom {0, 0, 0, 0};
    unit_t _level {0};

    /// The item is visible if @c true
    bool _visible {true};

    /// The item receives mouse and keyboard events if @c true.
    bool _enabled {true};

    /// The item in focus now if @c true.
    bool _focused {false};

    float _scale_factor_x {1.0f};
    float _scale_factor_y {1.0f};
    float _rotation {0.0f};

public:
    item () = default;
    virtual ~item () = default;

    constexpr unit_t x () const noexcept { return _geom.x; }
    constexpr unit_t y () const noexcept { return _geom.y; }
    constexpr unit_t width () const noexcept { return _geom.w; }
    constexpr unit_t height () const noexcept { return _geom.h; }
    constexpr unit_t level () const noexcept { return _level; }
    constexpr bool visible () const noexcept { return _visible; }
    constexpr bool enabled () const noexcept { return _enabled; }

    virtual void set_position (unit_t x, unit_t y)
    {
        _geom.x = x;
        _geom.y = y;
    }

    void set_x (unit_t value) { _geom.x = value; }
    void set_y (unit_t value) { _geom.y = value; }
    void set_width (unit_t value) { _geom.w = value; }
    void set_height (unit_t value) { _geom.h = value; }
    void set_level (unit_t value) { _level = value; }
    void set_visible (bool value) { _visible = value; }
    void set_enabled (bool value) { _enabled = value; }

    geom_t geometry () const noexcept
    {
        return _geom;
    }

    void set_geometry (geom_t const & g)
    {
        _geom = g;
    }

    size_t size () const noexcept
    {
        return size_t {_geom.w, _geom.h};
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
