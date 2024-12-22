////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.07 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace griotte {

// Must be signed
using unit_t = float;

struct point2d
{
    unit_t x, y;
};

struct size2d
{
    unit_t w, h;
};

struct rect2d
{
    unit_t x1, y1; // top-left corner
    unit_t x2, y2; // bottom-right corner
};

// Geometry
struct geom2d
{
    unit_t x, y; // top-left corner
    unit_t w, h; // size
};

using point_t = point2d;
using size_t  = size2d;
using rect_t  = rect2d;
using geom_t  = geom2d;

} // namespace griotte
