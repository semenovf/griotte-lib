////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.12.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include <pfs/griotte/linear_layout.hpp>
#include <pfs/griotte/color.hpp>
#include <pfs/griotte/rectangle.hpp>
#include <pfs/griotte/SFML/ui.hpp>
#include <vector>

using palette_t = std::array<griotte::color_t, 5>;

// https://www.color-hex.com/color-palette/1053661
// [Pantone Color of the Year 2025](https://www.pantone.com/color-of-the-year/2025)
palette_t mocha_mousse = {
      griotte::color_t{164,120,100} // #a47864
    , griotte::color_t{181,134,112} // #b58670
    , griotte::color_t{167,136,122} // #a7887a
    , griotte::color_t{149,124,113} // #957c71
    , griotte::color_t{166,112, 87} // #a67057
};

std::vector<palette_t> palettes = {
    mocha_mousse
};

void palette (griotte::SFML::ui & ui, int palette_index)
{
    auto & l = ui.acquire_layout<griotte::linear_layout>(griotte::orientation::horizontal);

    auto & r1 = l.create<griotte::rectangle>();
    auto & r2 = l.create<griotte::rectangle>();
    auto & r3 = l.create<griotte::rectangle>();
    auto & r4 = l.create<griotte::rectangle>();
    auto & r5 = l.create<griotte::rectangle>();

    auto i = palette_index % palettes.size();

    r1.set_color(palettes[i][0]);
    r2.set_color(palettes[i][1]);
    r3.set_color(palettes[i][2]);
    r4.set_color(palettes[i][3]);
    r5.set_color(palettes[i][4]);
}

