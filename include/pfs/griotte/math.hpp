////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.18 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "unit.hpp"

namespace griotte {

inline rect2d center_in (rect2d const & r, dim2d const & d)
{
    rect2d result;
    result.a.x = r.a.x + (r.b.x - r.a.x - d.w) / 2;
    result.a.y = r.a.y + (r.b.y - r.a.y - d.h) / 2;
    result.b.x = result.a.x + d.w;
    result.b.y = result.a.y + d.h;
    return result;
}

inline geom2d center_in (geom2d const & r, dim2d const & d)
{
    geom2d result;
    result.a.x = r.a.x + (r.b.w - d.w) / 2;
    result.a.y = r.a.y + (r.b.h - d.h) / 2;
    result.b.w = d.w;
    result.b.h = d.h;
    return result;
}

} // namespace griotte
