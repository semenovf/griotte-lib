////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.12.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include <pfs/griotte/color.hpp>
#include <pfs/griotte/linear_layout.hpp>
#include <pfs/griotte/rectangle.hpp>
#include <pfs/griotte/SFML/ui.hpp>
#include <pfs/fmt.hpp>
#include <array>
#include <utility>
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

// https://www.color-hex.com/color-palette/1038444
// [Pantone Color of the Year 2024](https://www.pantone.com/color-of-the-year/2024)
palette_t peach_fuzz = {
      griotte::color_t{254,213,188} // #fed5bc
    , griotte::color_t{254,172,122} // #feac7a
    , griotte::color_t{254,190,152} // #febe98
    , griotte::color_t{254,231,216} // #fee7d8
    , griotte::color_t{254,153, 92} // #fe995c
};

// https://www.color-hex.com/color-palette/1029870
// [Pantone Color of the Year 2023](https://www.pantone.com/color-of-the-year/2023)
palette_t viva_magenta = {
      griotte::color_t{ 85, 17, 32} // #551120
    , griotte::color_t{136, 28, 52} // #881c34
    , griotte::color_t{187, 38, 73} // #bb2649
    , griotte::color_t{221, 87,117} // #dd5775
    , griotte::color_t{232,140,160} // #e88ca0
};

std::vector<std::pair<std::string, palette_t>> palettes = {
      { "Mocha Mousse", mocha_mousse }
    , { "Peach Fuzz"  , peach_fuzz }
    , { "Viva Magenta", viva_magenta }
};

void palette (griotte::SFML::ui & ui, int palette_index)
{
    auto i = palette_index % palettes.size();
    fmt::println("Palette: {}", palettes[i].first);

    auto & l = ui.create_layout<griotte::linear_layout>(griotte::orientation::horizontal);

    auto & r1 = l.create<griotte::rectangle>();
    auto & r2 = l.create<griotte::rectangle>();
    auto & r3 = l.create<griotte::rectangle>();
    auto & r4 = l.create<griotte::rectangle>();
    auto & r5 = l.create<griotte::rectangle>();

    // l.set_margins(r2, 10);
    // l.set_preferred_width(r2, 50);

    r1.set_color(palettes[i].second[0]);
    r2.set_color(palettes[i].second[1]);
    r3.set_color(palettes[i].second[2]);
    r4.set_color(palettes[i].second[3]);
    r5.set_color(palettes[i].second[4]);
}
