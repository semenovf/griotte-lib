////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.12 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include <pfs/griotte/logger.hpp>
#include <pfs/griotte/font.hpp>
#include <pfs/griotte/SFML/ui.hpp>
#include <pfs/argvapi.hpp>
#include <pfs/filesystem.hpp>
#include <pfs/i18n.hpp>
#include <pfs/string_view.hpp>
#include <cmrc/cmrc.hpp>
#include <array>
#include <cstdlib>
#include <utility>

CMRC_DECLARE(rc::icons);

static constexpr int SCREEN_WIDTH = 640;
static constexpr int SCREEN_HEIGHT = 480;

namespace fs = pfs::filesystem;
using griotte::logger;

extern void anchors_layout (griotte::SFML::ui &);
extern void fixed_layout (griotte::SFML::ui &);
extern void scale (griotte::SFML::ui &);
extern void palette (griotte::SFML::ui &, int palette_index);

namespace constants {

static std::array<std::pair<std::string, fs::path>, 2> const fonts = {
      std::pair{"Inter", PFS__LITERAL_PATH("Inter.ttf")}
    , std::pair{"Roboto", PFS__LITERAL_PATH("Roboto-Regular.ttf")}
};

} // namespace constants

static void dump_embedded_fonts ()
{
    auto emfonts = griotte::font::embedded_fonts();

    fmt::println("Embedded fonts:");
    int counter = 0;

    for (auto const & alias: emfonts) {
        fmt::println("    {}. {}", ++counter, alias);
    }
}

static void print_help (std::string const & progname)
{
    fmt::println("Usage:");
    fmt::println("  {} --help", progname);
    fmt::println("  {} fixed-layout | fl", progname);
    fmt::println("  {} anchors-layout | al", progname);
    fmt::println("  {} scale", progname);
    fmt::println("  {} palette_INDEX", progname);
}

int main (int argc, char * argv[])
{
    griotte::SFML::ui::options opts;
    opts.x = 0;
    opts.y = 0;
    opts.w = SCREEN_WIDTH;
    opts.h = SCREEN_HEIGHT;
    opts.title = "SFML Demo";

    dump_embedded_fonts();

    griotte::SFML::ui ui {std::move(opts)};

    for (auto const & f: constants::fonts) {
        if (griotte::font::load(f.first, f.second)) {
            logger::d(tr::f_("Font loaded: {} => {}", f.first, f.second));
        } else {
            return EXIT_FAILURE;
        }
    }

    ui.set_color(griotte::color_t{0xFF, 0xF8, 0xF2});

    auto cl = pfs::make_argvapi(argc, argv);
    auto it = cl.begin();

    if (it.has_more()) {
        auto x = it.next();

        if (x.is_option()) {
            if (x.optname() == "help") {
                print_help(pfs::filesystem::utf8_encode(cl.program_name()));
                return EXIT_SUCCESS;
            } else {
                fmt::println(stderr, "Bad option or command name");
                return EXIT_FAILURE;
            }
        } else {
            if (x.arg() == "al" || x.arg() == "anchors-layout")
                anchors_layout(ui);
            else if (x.arg() == "fl" || x.arg() == "fixed-layout")
                fixed_layout(ui);
            else if (x.arg() == "scale")
                scale(ui);
            else if (pfs::starts_with(x.arg(), "palette_")) {
                auto index = std::stoi(std::string(x.arg().begin() + 8, x.arg().begin() + x.arg().size()));
                palette(ui, index);
            } else
                fixed_layout(ui);
        }
    } else {
        fixed_layout(ui);
    }

    ui.run();

    return EXIT_SUCCESS;
}
