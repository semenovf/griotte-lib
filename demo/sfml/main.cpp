////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.12 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include <griotte/fixed_layout.hpp>
#include <griotte/fontstyle.hpp>
#include <griotte/logger.hpp>
#include <griotte/math.hpp>
#include <griotte/rectangle.hpp>
#include <griotte/text.hpp>
#include <griotte/SFML/font.hpp>
#include <griotte/SFML/ui.hpp>
#include <pfs/filesystem.hpp>
#include <pfs/i18n.hpp>
#include <array>
#include <cstdlib>
#include <utility>

static constexpr int SCREEN_WIDTH = 640;
static constexpr int SCREEN_HEIGHT = 480;

namespace fs = pfs::filesystem;
using griotte::logger;

namespace constants {

static std::array<std::pair<std::string, fs::path>, 2> const fonts = {
      std::pair{"Inter", PFS__LITERAL_PATH("Inter.ttf")}
    , std::pair{"Roboto", PFS__LITERAL_PATH("Roboto-Regular.ttf")}
};

} // namespace constants

int main ([[maybe_unused]] int argc, [[maybe_unused]] char * argv[])
{
    griotte::SFML::ui::options opts;
    opts.x = 0;
    opts.y = 0;
    opts.w = SCREEN_WIDTH;
    opts.h = SCREEN_HEIGHT;
    opts.title = "SFML Demo";

    griotte::SFML::ui ui {std::move(opts)};

    for (auto const & f: constants::fonts) {
        if (griotte::SFML::font::load_font(f.first, f.second)) {
            logger::d(tr::f_("Font loaded: {} => {}", f.first, f.second));
        } else {
            return EXIT_FAILURE;
        }
    }

    ui.set_color(griotte::color_t{0xFF, 0xF8, 0xF2});

    auto & l = ui.acquire_layout<griotte::fixed_layout>();

    griotte::unit_t y = 10;
    griotte::unit_t margin = 10;

    auto & r1 = l.create<griotte::rectangle>();
    r1.set_x(10);
    r1.set_y(y);
    r1.set_width(400);
    r1.set_height(80);
    r1.set_radius(30);
    r1.set_color(griotte::color_t {0xFA, 0xEF, 0xDF});

    y += r1.height() + margin;

    auto & r2 = l.create<griotte::rectangle>();
    r2.set_x(r1.x());
    r2.set_y(y);
    r2.set_width(r1.width());
    r2.set_height(r1.height());
    r2.set_radius(r1.radius());
    r2.set_color(r1.color());

    y += r2.height() + margin;

    auto & r3 = l.create<griotte::rectangle>();
    r3.set_x(r1.x());
    r3.set_y(y);
    r3.set_width(r1.width());
    r3.set_height(r1.height());
    r3.set_radius(r1.radius());
    r3.set_color(r1.color());

    y += r3.height() + margin;

    auto & r4 = l.create<griotte::rectangle>();
    r4.set_x(r1.x());
    r4.set_y(y);
    r4.set_width(r1.width());
    r4.set_height(r1.height());
    r4.set_radius(r1.radius());
    r4.set_color(r1.color());

    y += r3.height() + margin;

    auto & r5 = l.create<griotte::rectangle>();
    r5.set_x(r1.x());
    r5.set_y(y);
    r5.set_width(r1.width());
    r5.set_height(r1.height());
    r5.set_radius(r1.radius());
    r5.set_color(r1.color());

    ////////////////////////////////////////////////////////////////////////////////////////////////

    griotte::unit_t radius = 26;

    auto & s1 = l.create<griotte::rectangle>();
    s1.set_radius(radius);
    s1.set_color(griotte::color_t {0xE9, 0xB1, 0x10});

    auto g1 = griotte::center_in(r1.geometry(), griotte::dim_t{radius * 2, radius * 2});
    s1.set_geometry(g1);
    s1.set_x(r1.x() + margin);

    auto & s2 = l.create<griotte::rectangle>();
    s2.set_radius(radius);
    s2.set_color(griotte::color_t {0xFF, 0xB2, 0xB3});

    auto g2 = griotte::center_in(r2.geometry(), griotte::dim_t{radius * 2, radius * 2});
    s2.set_geometry(g2);
    s2.set_x(r2.x() + margin);

    auto & s3 = l.create<griotte::rectangle>();
    s3.set_radius(radius);
    s3.set_color(griotte::color_t {0x50, 0x3F, 0x0D});

    auto g3 = griotte::center_in(r3.geometry(), griotte::dim_t{radius * 2, radius * 2});
    s3.set_geometry(g3);
    s3.set_x(r3.x() + margin);

    auto & s4 = l.create<griotte::rectangle>();
    s4.set_radius(radius);
    s4.set_color(griotte::color_t {0xBA, 0x1B, 0x1B});

    auto g4 = griotte::center_in(r4.geometry(), griotte::dim_t{radius * 2, radius * 2});
    s4.set_geometry(g4);
    s4.set_x(r4.x() + margin);

    auto & s5 = l.create<griotte::rectangle>();
    s5.set_radius(radius);
    s5.set_color(griotte::color_t {0xE6, 0xD4, 0xC9});

    auto g5 = griotte::center_in(r5.geometry(), griotte::dim_t{radius * 2, radius * 2});
    s5.set_geometry(g5);
    s5.set_x(r5.x() + margin);

    ////////////////////////////////////////////////////////////////////////////////////////////////

    griotte::fontstyle font_style1;
    font_style1.add_bold();

    auto font1 = griotte::font_t::get_font(constants::fonts[0].first);

    auto & t1 = l.create<griotte::text>("Hello world");
    t1.set_font(font1);
    t1.set_font_style(font_style1);
    t1.set_pixel_size(24);
    t1.set_color(griotte::color_t {0xFF, 0x00, 0x00}); // Red

    auto font2 = griotte::font_t::get_font(constants::fonts[1].first);

    auto & t2 = l.create<griotte::text>("Hello another world");
    t2.set_x(10);
    t2.set_y(100);
    t2.set_font(font2);
    t2.set_pixel_size(24);
    t2.set_color(griotte::color_t {0x26, 0x46, 0x53});

    ////////////////////////////////////////////////////////////////////////////////////////////////

    ui.run();

    return EXIT_SUCCESS;
}
