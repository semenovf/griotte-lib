////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "circle.hpp"

namespace griotte {

unit_t circle::radius () const noexcept
{
    return _geom.w / 2;
}

void circle::set_radius (unit_t value)
{
    _geom.w = _geom.h = value * 2;
}

point_t circle::origin () const noexcept
{
    return point_t{ _geom.x + _geom.w / 2, _geom.y + _geom.w / 2};
}

void circle::set_origin (unit_t x, unit_t y)
{
    _geom.x = x - _geom.w / 2;
    _geom.y = y - _geom.w / 2;
}

} // namespace griotte
