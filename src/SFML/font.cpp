////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "casting.hpp"
#include "font_impl.hpp"
#include "log_guard.hpp"
#include "logger.hpp"
#include <pfs/i18n.hpp>
#include <array>

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
};

static std::array<font_resource, 2> const static_font_resources {
    // First font is fallback font by default
      font_resource{"roboto-regular", Roboto_Regular_ttf, Roboto_Regular_ttf_len}
    , font_resource{"inter-regular", Inter_Regular_ttf, Inter_Regular_ttf_len}
};

std::unordered_map<std::string, std::unique_ptr<font::impl>> font::impl::s_fonts;
font::impl * font::impl::s_fallback_font {nullptr};

bool font::impl::add (std::string const & alias, std::unique_ptr<impl> && f, bool is_fallback)
{
    if (s_fonts.find(alias) != s_fonts.end()) {
        logger::e(tr::f_("font alias already occupied by font: {}", alias));
        return false;
    }

    f->setSmooth(true);

    s_fonts[alias] = std::move(f);

    if (is_fallback)
        s_fallback_font = s_fonts[alias].get();

    return true;
}

font::font (impl * d)
    : _d(d)
{}

font::operator bool () const noexcept
{
    return _d != nullptr;
}

void * font::native ()
{
    return _d;
}

// [static]
std::vector<std::string> font::embedded_fonts ()
{
    std::vector<std::string> result;
    result.reserve(static_font_resources.size());

    for (auto const & f: static_font_resources) {
        result.push_back(std::string{f.alias});
    }

    return result;
}

// [static]
bool font::load ()
{
    return load(static_font_resources[0].alias, true);
}

// [static]
bool font::load (std::string const & font_alias, bool is_fallback)
{
    for (auto const & item: static_font_resources) {
        if (item.alias == font_alias) {
            log_guard lg;

            auto f = std::make_unique<impl>();
            auto success = f->loadFromMemory(item.data, item.len);

            if (success)
                return impl::add(font_alias, std::move(f), is_fallback);

            return false;
        }
    }

    logger::e(tr::f_("embedded font not found: {}", font_alias));
    return false;
}


// [static]
bool font::load (std::string const & font_alias, pfs::filesystem::path const & path, bool is_fallback)
{
    auto f = std::make_unique<impl>();
    log_guard lg;

    if (!f->loadFromFile(pfs::utf8_encode_path(path)))
        return false;

    return impl::add(font_alias, std::move(f), is_fallback);
}

// [static]
font font::get (std::string const & font_alias, font fallback_font)
{
    auto pos = impl::s_fonts.find(font_alias);

    if (pos == impl::s_fonts.end())
        return fallback_font;

    return font {& *pos->second};
}

font font::get (std::string const & font_alias)
{
    return get(font_alias, font(impl::s_fallback_font));
}

font font::get ()
{
    return font {impl::s_fallback_font};
}

} // namespace griotte::SFML
