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

//
// [OpenGL Programming/Modern OpenGL Tutorial Text Rendering 01](https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_01)
//

static std::vector<std::string> font_filenames {
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

static std::string font_dir {"resources/fonts/"};

int main ()
{
    pfs::griotte::context app;

    if (!app.good()) {
        fmt::print("ERROR: {}", app.errorstr());
        return -1;
    }

    // Load font
    auto font_path = font_dir + font_filenames[0];
    auto font = app.load_font(font_path, 0);

    if (font) {
        bool ok = true;
        if (ok)
            font.set_pixel_size(48, & ok);

        if (ok)
            font.load_char('X', & ok);

        if (!ok) {
            fmt::print("ERROR: font operations failed");
        }
    }

    return 0;
}
