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
#include "transform.hpp"

namespace griotte {

inline rect2d center_in (rect2d const & r, size2d const & d)
{
    rect2d result;
    result.x1 = r.x1 + (r.x2 - r.x1 - d.w) / 2;
    result.y1 = r.y1 + (r.y2 - r.y1 - d.h) / 2;
    result.x2 = result.x1 + d.w;
    result.y2 = result.y1 + d.h;
    return result;
}

inline geom2d center_in (geom2d const & r, size2d const & d)
{
    geom2d result;
    result.x = r.x + (r.w - d.w) / 2;
    result.y = r.y + (r.h - d.h) / 2;
    result.w = d.w;
    result.h = d.h;
    return result;
}

template <typename Float>
inline geom2d apply (transform<Float> & t, geom2d const & g)
{
    geom2d result;
    t.map(g.x, g.y, g.w, g.h, & result.x, & result.y, & result.w, & result.h);
    return result;
}

} // namespace griotte
