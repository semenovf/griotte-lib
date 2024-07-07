////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.07 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "unit.hpp"
#include <deque>

namespace griotte {

class item
{
protected:
    unit_t _x {0};
    unit_t _y {0};
    unit_t _z {0};
    unit_t _width {0};
    unit_t _height {0};

    /// The item is visible if @c true
    bool _visible {true};

    /// The item receives mouse and keyboard events if @c true.
    bool _enabled {true};

    std::deque<item *> _children;

public:
    item () = default;
    ~item () = default;

    constexpr unit_t x () const noexcept { return _x; }
    constexpr unit_t y () const noexcept { return _y; }
    constexpr unit_t z () const noexcept { return _z; }
    constexpr unit_t width () const noexcept { return _width; }
    constexpr unit_t height () const noexcept { return _height; }
    constexpr bool visible () const noexcept { return _visible; }
    constexpr bool enabled () const noexcept { return _enabled; }

    void set_x (unit_t value) { _x = value; }
    void set_y (unit_t value) { _y = value; }
    void set_z (unit_t value) { _z = value; }
    void set_width (unit_t value) { _width = value; }
    void set_height (unit_t value) { _height = value; }
    void set_visible (bool value) { _visible = value; }
    void set_enabled (bool value) { _enabled = value; }
};

} // namespace griotte
