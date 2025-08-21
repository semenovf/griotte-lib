////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024-2025 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.19 Initial version.
//      2025.08.21 Refused to use PIMPL idiom.
////////////////////////////////////////////////////////////////////////////////
#include "griotte/font.hpp"
#include "casting.hpp"
#include "log_guard.hpp"
#include "logger.hpp"
#include "SFML/Graphics/Font.hpp"
#include <pfs/assert.hpp>
#include <pfs/i18n.hpp>
#include <array>
#include <unordered_map>

namespace griotte {

extern "C" unsigned char Roboto_Regular_ttf[];
extern "C" unsigned int Roboto_Regular_ttf_len;
extern "C" unsigned char Inter_Regular_ttf[];
extern "C" unsigned int Inter_Regular_ttf_len;

struct font_resource
{
    char const * alias;
    unsigned char * data;
    unsigned int len;
    sf::Font * font_ptr;
};

// First font is fallback font by default.
static std::array<font_resource, 2> static_font_resources {
      font_resource{"roboto-regular", Roboto_Regular_ttf, Roboto_Regular_ttf_len, nullptr}
    , font_resource{"inter-regular", Inter_Regular_ttf, Inter_Regular_ttf_len, nullptr}
};

std::unordered_map<std::string, std::unique_ptr<sf::Font>> static_fonts;
std::string static_fallback_font_alias;

static bool add (std::string const & alias, std::unique_ptr<sf::Font> && f, bool is_fallback)
{
    if (static_fonts.find(alias) != static_fonts.end()) {
        logger::e(tr::f_("font alias already occupied by font: {}", alias));
        return false;
    }

    f->setSmooth(true);

    static_fonts[alias] = std::move(f);

    if (is_fallback || static_fonts.size() == 1)
        static_fallback_font_alias = alias;

    return true;
}

font_t::font_t ()
{}

font_t::font_t (std::string const & alias)
{
    if (static_fonts.empty()) {
        auto success = load(static_font_resources[0].alias, true);
        PFS__THROW_UNEXPECTED(success, "Unable to load font from resources");
    }

    auto pos = static_fonts.find(alias);

    if (pos == static_fonts.end()) {
        logger::e(tr::f_("font not found: {}, using fallback font: {}", alias, static_fallback_font_alias));
        _alias = static_fallback_font_alias;
        return;
    }
}

// [static]
std::vector<std::string> font_t::fonts_available ()
{
    std::vector<std::string> result = fonts_loaded();

    for (auto const & elem: static_font_resources) {
        auto contains = (static_fonts.find(elem.alias) != static_fonts.end());

        if (!contains)
            result.push_back(elem.alias);
    }

    return result;
}

// [static]
std::vector<std::string> font_t::fonts_loaded ()
{
    std::vector<std::string> result;
    result.reserve(static_fonts.size());

    for (auto const & elem: static_fonts)
        result.push_back(elem.first);

    return result;
}

// [static]
bool font_t::load (std::string const & font_alias, bool is_fallback)
{
    for (auto & font_res: static_font_resources) {
        if (font_res.alias == font_alias) {
            if (font_res.font_ptr != nullptr) {
                log_guard lg;

                auto f = std::make_unique<sf::Font>();
                auto success = f->loadFromMemory(font_res.data, font_res.len);

                if (success) {
                    font_res.font_ptr = f.get();
                    return add(font_alias, std::move(f), is_fallback);
                }

                return false;
            } else {
                if (is_fallback)
                    static_fallback_font_alias = font_alias;

                return true;
            }
        }
    }

    logger::e(tr::f_("embedded font not found: {}", font_alias));
    return false;
}


// [static]
bool font_t::load (std::string const & font_alias, pfs::filesystem::path const & path, bool is_fallback)
{
    auto f = std::make_unique<sf::Font>();
    log_guard lg;

    if (!f->loadFromFile(pfs::utf8_encode_path(path)))
        return false;

    return add(font_alias, std::move(f), is_fallback);
}

font_t font_t::get (std::string const & font_alias)
{
    if (font_alias.empty())
        return get();

    auto pos = static_fonts.find(font_alias);

    if (pos == static_fonts.end()) {
        logger::e(tr::f_("font not found: {}, using fallback font: {}"
            , font_alias, static_fallback_font_alias));
        return font_t {static_fallback_font_alias};
    }

    return font_t {pos->first};
}

font_t font_t::get ()
{
    return font_t {static_fallback_font_alias};
}

// For external use
sf::Font const & native_font (font_t const & f)
{
    auto const & font_alias = f.alias();
    auto pos = static_fonts.find(font_alias.empty()
        ? static_fallback_font_alias
        : font_alias);
    PFS__THROW_UNEXPECTED(pos != static_fonts.end(), "Fix font algorithms");
    return *pos->second;
}

} // namespace griotte::SFML
