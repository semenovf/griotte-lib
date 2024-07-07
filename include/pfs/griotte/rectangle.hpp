////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.07 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "item.hpp"
#include "bordered.hpp"
#include <deque>

namespace griotte {

class rectangle: public item, public bordered
{
protected:
    unit_t _radius {0};

public:
    rectangle (): item () {}
    ~rectangle () = default;

    constexpr unit_t radius () const noexcept { return _radius; }

    void set_radius (unit_t value) { _radius = value; }
};

} // namespace griotte
