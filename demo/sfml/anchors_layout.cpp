
////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.30 Initial version.
////////////////////////////////////////////////////////////////////////////////
// #include <pfs/griotte/circle.hpp>
#include <pfs/griotte/anchors_layout.hpp>
// #include <pfs/griotte/fontstyle.hpp>
// #include <pfs/griotte/image.hpp>
// #include <pfs/griotte/math.hpp>
#include <pfs/griotte/rectangle.hpp>
// #include <pfs/griotte/SFML/text.hpp>
// #include <pfs/griotte/SFML/font.hpp>
#include <pfs/griotte/SFML/ui.hpp>
#include <pfs/log.hpp>

void anchors_layout (griotte::SFML::ui & ui)
{
    auto & l = ui.acquire_layout<griotte::anchors_layout>();

    auto & r1 = l.create<griotte::rectangle>();
    l.fill(r1, l);
    l.set_margins(r1, griotte::unit_t{20});
    r1.set_color(griotte::color_t {0xE7, 0x6F, 0x51});

    auto & r2 = l.create<griotte::rectangle>();
    l.fill(r2, l);
    l.set_margins(r2, griotte::unit_t{40});
    r2.set_color(griotte::color_t {0x2A, 0x9D, 0x8F});

    // Rectangle in the top-left corner
    auto & r3 = l.create<griotte::rectangle>();
    l.set_left(r3, r2, griotte::anchor_spot::left, griotte::unit_t{10});
    l.set_top(r3, r2, griotte::anchor_spot::top, griotte::unit_t{10});
    l.set_width(r3, 60);
    l.set_height(r3, 60);
    r3.set_color(griotte::color_t {0x83, 0x38, 0xEC});

    // Rectangle in the top-right corner
    auto & r4 = l.create<griotte::rectangle>();
    l.set_right(r4, r2, griotte::anchor_spot::right, griotte::unit_t{10});
    l.set_top(r4, r2, griotte::anchor_spot::top, griotte::unit_t{10});
    l.set_width(r4, 80);
    l.set_height(r4, 80);
    r4.set_color(griotte::color_t {0xC1, 0x12, 0x1F});

    // Rectangle in the bottom-right corner
    auto & r5 = l.create<griotte::rectangle>();
    l.set_right(r5, r2, griotte::anchor_spot::right, griotte::unit_t{10});
    l.set_bottom(r5, r2, griotte::anchor_spot::bottom, griotte::unit_t{10});
    l.set_width(r5, 100);
    l.set_height(r5, 100);
    r5.set_color(griotte::color_t {0xE9, 0xC4, 0x6A});

    // Rectangle in the bottom-left corner
    auto & r6 = l.create<griotte::rectangle>();
    l.set_left(r6, r2, griotte::anchor_spot::left, griotte::unit_t{10});
    l.set_bottom(r6, r2, griotte::anchor_spot::bottom, griotte::unit_t{10});
    l.set_width(r6, 120);
    l.set_height(r6, 120);
    r6.set_color(griotte::color_t {0xE4, 0xC1, 0xF9});
}
