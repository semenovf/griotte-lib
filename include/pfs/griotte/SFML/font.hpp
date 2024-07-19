////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <pfs/filesystem.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace sf {
class Font;
}

namespace griotte {
namespace SFML {

class font
{
private:
    sf::Font const * _f {nullptr};

private: // static
    static std::unordered_map<std::string, std::unique_ptr<sf::Font>> static_fonts;
    static font static_fallback_font;

private:
    font (sf::Font const * f): _f (f) {}

public:
    font () = default;
    ~font () = default;

    operator bool () const noexcept
    {
        return _f != nullptr;
    }

    operator sf::Font const * () const noexcept
    {
        return _f;
    }

public: // static
    static bool load_font (std::string const & font_alias, pfs::filesystem::path const & path, bool is_fallback = false);
    static font get_font (std::string const & font_alias, font fallback_font = static_fallback_font);
};

}} // namespace griotte::SFML
