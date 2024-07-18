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

struct dim2d
{
    unit_t w, h;
};

struct rect2d
{
    point2d a; // top-left corner
    point2d b; // bottom-right corener
};

// Geometry
struct geom2d
{
    point2d a;     // top-left corner
    dim2d b; // size
};

using point_t = point2d;
using dim_t   = dim2d;
using rect_t  = rect2d;
using geom_t  = geom2d;

} // namespace griotte
