
////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.30 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include <pfs/griotte/circle.hpp>
#include <pfs/griotte/anchors_layout.hpp>
#include <pfs/griotte/rectangle.hpp>
#include <pfs/griotte/SFML/ui.hpp>
#include <pfs/log.hpp>

void anchors_layout (griotte::SFML::ui & ui)
{
    auto & l = ui.create_layout<griotte::anchors_layout>();

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

    // Circle in the center
    auto & c1 = l.create<griotte::circle>();
    c1.set_radius(griotte::unit_t{80});
    c1.set_color(griotte::color_t {0xFF, 0xD5, 0x00});
    l.set_hcenter(c1, r2, griotte::anchor_spot::hcenter, griotte::unit_t{0});
    l.set_vcenter(c1, r2, griotte::anchor_spot::vcenter, griotte::unit_t{10});

    // Circle inside c1
    auto & c2 = l.create<griotte::circle>();
    c2.set_radius(griotte::unit_t{40});
    c2.set_color(griotte::color_t {0x5F, 0xA8, 0xD3});
    l.center_in(c2, c1);

    // Rectangle bitween `r3` and `r4`
    auto & r7 = l.create<griotte::rectangle>();
    l.set_left(r7, r3, griotte::anchor_spot::right, griotte::unit_t{5});
    l.set_right(r7, r4, griotte::anchor_spot::left, griotte::unit_t{5});
    l.set_height(r7, 20);
    l.set_vcenter(r7, r3, griotte::anchor_spot::vcenter, griotte::unit_t{0});
    r7.set_color(griotte::color_t {0x9D, 0x81, 0x89});

    // Circle c3 horizontally centered relative to the left side of c1
    auto & c3 = l.create<griotte::circle>();
    c3.set_radius(griotte::unit_t{30});
    c3.set_color(griotte::color_t {0x06, 0xD6, 0xA0});
    l.set_hcenter(c3, c1, griotte::anchor_spot::left, griotte::unit_t{0});
    l.set_vcenter(c3, c1, griotte::anchor_spot::vcenter, griotte::unit_t{0});

    // Circle c4 vertically centered relative to the top side of c1
    auto & c4 = l.create<griotte::circle>();
    c4.set_radius(griotte::unit_t{30});
    c4.set_color(griotte::color_t {0xFF, 0x00, 0x54});
    l.set_hcenter(c4, c1, griotte::anchor_spot::hcenter, griotte::unit_t{0});
    l.set_vcenter(c4, c1, griotte::anchor_spot::top, griotte::unit_t{0});

    // Rectangle inside `r6`
    auto & r8 = l.create<griotte::rectangle>();
    r8.set_width(r6.width() / 2 - 5);
    r8.set_height(r6.height() / 2 - 5);
    l.set_left(r8, r6, griotte::anchor_spot::hcenter, griotte::unit_t{0});
    l.set_top(r8, r6, griotte::anchor_spot::vcenter, griotte::unit_t{0});
    r8.set_color(griotte::color_t {0xFF, 0x66, 0xB3});

    // Rectangle bitween `r6` and `r5`
    auto & r9 = l.create<griotte::rectangle>();
    l.set_left(r9, r6, griotte::anchor_spot::right, griotte::unit_t{5});
    l.set_right(r9, r5, griotte::anchor_spot::right, griotte::unit_t{0});
    l.set_height(r9, 30);
    l.set_vcenter(r9, r5, griotte::anchor_spot::vcenter, griotte::unit_t{0});
    r9.set_color(griotte::color_t {0x70, 0xD6, 0xFF});

    // Rectangle bitween `r3` and `r6`
    auto & r10 = l.create<griotte::rectangle>();
    l.set_top(r10, r3, griotte::anchor_spot::bottom, griotte::unit_t{5});
    l.set_bottom(r10, r6, griotte::anchor_spot::vcenter, griotte::unit_t{0});
    l.set_width(r10, 25);
    l.set_hcenter(r10, r3, griotte::anchor_spot::hcenter, griotte::unit_t{0});
    r10.set_color(griotte::color_t {0x4A, 0x57, 0x59});
}
