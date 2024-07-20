////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.20 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "log_guard.hpp"
#include "griotte/SFML/font.hpp"
#include "griotte/logger.hpp"
#include <pfs/i18n.hpp>
#include <pfs/memory.hpp>
#include <SFML/Graphics/Font.hpp>
#include <array>

namespace griotte {
namespace SFML {

extern "C" unsigned char Roboto_Regular_ttf[];
extern "C" unsigned int Roboto_Regular_ttf_len;

struct font_resource
{
    char const * alias;
    unsigned char * data;
    unsigned int len;
};

static std::array<font_resource, 1> const static_font_resources {
    // First font is fallback font by default
    font_resource{"roboto-regular", Roboto_Regular_ttf, Roboto_Regular_ttf_len}
};

// [static]
std::vector<std::string> font::embeded_fonts ()
{
    std::vector<std::string> result;
    result.reserve(static_font_resources.size());

    for (auto const & f: static_font_resources) {
        result.push_back(std::string{f.alias});
    }

    return result;
}

// [static]
bool font::load_font ()
{
    return load_font(static_font_resources[0].alias, true);
}

// [static]
bool font::load_font (std::string const & font_alias, bool is_fallback)
{
    for (auto const & item: static_font_resources) {
        if (item.alias == font_alias) {
            log_guard lg;

            auto f = pfs::make_unique<sf::Font>();
            auto success = f->loadFromMemory(item.data, item.len);

            if (success)
                return add_font(font_alias, std::move(f), is_fallback);

            return false;
        }
    }

    logger::e(tr::f_("embedded font not found: {}", font_alias));
    return false;
}

}} // namespace griotte::SFML

