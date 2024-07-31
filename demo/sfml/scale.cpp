////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.23 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include <pfs/griotte/fixed_layout.hpp>
#include <pfs/griotte/math.hpp>
#include <pfs/griotte/rectangle.hpp>
#include <pfs/griotte/transform.hpp>
#include <pfs/griotte/SFML/ui.hpp>

void scale (griotte::SFML::ui & ui)
{
    auto & l = ui.acquire_layout<griotte::fixed_layout>();

    auto & r1 = l.create<griotte::rectangle>();
    r1.set_width(400);
    r1.set_height(300);
    r1.set_color(griotte::color_t {0x2A, 0x92, 0x8f});

    auto g1 = griotte::center_in(griotte::geom_t{ 0, 0, ui.width_units(), ui.height_units() }
        , griotte::dim_t{r1.width(), r1.height()});
    r1.set_geometry(g1);

    ////////////////////////////////////////////////////////////////////////////////////////////////

    griotte::transform_t t2;
    t2.scale(0.5);
    auto g2 = griotte::apply(t2, r1.geometry());
    g2 = griotte::center_in(r1.geometry(), griotte::dim_t{g2.w, g2.h});

    auto & r2 = l.create<griotte::rectangle>();
    r2.set_color(griotte::color_t {0xE7, 0x6F, 0x51});
    r2.set_geometry(g2);
}
