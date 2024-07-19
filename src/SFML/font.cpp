////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "casting.hpp"
#include "log_guard.hpp"
#include "griotte/SFML/font.hpp"
#include "griotte/logger.hpp"
#include <pfs/i18n.hpp>
#include <pfs/memory.hpp>
#include <SFML/Graphics/Font.hpp>
// #include <sstream>
// #include <thread>

namespace griotte {
namespace SFML {

std::unordered_map<std::string, std::unique_ptr<sf::Font>> font::static_fonts;
font font::static_fallback_font;

// [static]
bool font::load_font (std::string const & font_alias, pfs::filesystem::path const & path, bool is_fallback)
{
    auto f = pfs::make_unique<sf::Font>();
    log_guard lg;

    if (!f->loadFromFile(pfs::filesystem::utf8_encode(path))) {
        return false;
    }

    if (static_fonts.find(font_alias) != static_fonts.end()) {
        logger::e(tr::f_("font alias already occupied by font: {}, change font alias for file: {}"
            , font_alias, path));
        return false;
    }

    static_fonts[font_alias] = std::move(f);

    if (is_fallback)
        static_fallback_font = font {& *static_fonts[font_alias]};

    return true;
}

// [static]
font font::get_font (std::string const & font_alias, font fallback_font)
{
    auto pos = static_fonts.find(font_alias);

    if (pos == static_fonts.end())
        return fallback_font;

    return font {& *pos->second};
}

}} // namespace griotte::SFML
