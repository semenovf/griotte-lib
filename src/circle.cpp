////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "griotte/circle.hpp"

namespace griotte {

unit_t circle::radius () const noexcept
{
    return _w / 2;
}

void circle::set_radius (unit_t value)
{
    _w = _h = value * 2;
}

point_t circle::origin () const noexcept
{
    return point_t{ _x + _w / 2, _y + _w / 2};
}

void circle::set_origin (unit_t x, unit_t y)
{
    _x = x - _w / 2;
    _y = y - _w / 2;
}

} // namespace griotte
