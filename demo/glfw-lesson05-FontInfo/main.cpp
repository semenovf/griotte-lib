////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019-2020 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.26 Initial version
////////////////////////////////////////////////////////////////////////////////
#include "pfs/griotte/context.hpp"
#include <string>
#include <vector>

#define INDENT_SPACE "    "

int main ()
{
    pfs::griotte::context app;

    if (!app.good()) {
        fmt::print("ERROR: {}", app.errorstr());
        return -1;
    }

    std::vector<std::string> fontfilenames {
          "Roboto-BlackItalic.ttf"
        , "Roboto-Black.ttf"
        , "Roboto-BoldItalic.ttf"
        , "Roboto-Bold.ttf"
        , "Roboto-Italic.ttf"
        , "Roboto-LightItalic.ttf"
        , "Roboto-Light.ttf"
        , "Roboto-MediumItalic.ttf"
        , "Roboto-Medium.ttf"
        , "Roboto-Regular.ttf"
        , "Roboto-ThinItalic.ttf"
        , "Roboto-Thin.ttf"
    };

    std::string font_dir = "resources/fonts/";

    for (auto const & filename: fontfilenames) {
        auto fontpath = font_dir + filename;

        auto face_count = app.font_faces_count(fontpath);
        fmt::print("{}: contains {} face(s)\n"
                , filename
                , face_count);

        for (int i = 0; i < face_count; i++) {
            auto font = app.load_font(fontpath, i);
            fmt::print(INDENT_SPACE "[{}]: contains {} glyphs\n"
                    , i
                    , font.glyphs_count());

            fmt::print(INDENT_SPACE INDENT_SPACE "style name    : \"{}\"\n"
                    , font.style_name());
            fmt::print(INDENT_SPACE INDENT_SPACE "family name   : \"{}\"\n"
                    , font.family_name());
            fmt::print(INDENT_SPACE INDENT_SPACE "style         : {}\n"
                    , to_string(font.style()));
            fmt::print(INDENT_SPACE INDENT_SPACE "scalable      : {}\n"
                    , font.is_scalable() ? "true" : "false");
            fmt::print(INDENT_SPACE INDENT_SPACE "has kerning   : {}\n"
                    , font.has_kerning() ? "true" : "false");
            fmt::print(INDENT_SPACE INDENT_SPACE "units per EM  : {}\n"
                    , font.units_per_em());
            fmt::print(INDENT_SPACE INDENT_SPACE "strikes count : {}\n"
                    , font.strikes_count());
            fmt::print(INDENT_SPACE INDENT_SPACE "charmaps count: {}\n"
                    , font.charmaps_count());
        }
    }

    return 0;
}
