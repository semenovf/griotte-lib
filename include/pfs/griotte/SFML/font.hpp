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

private: // static
    static bool add (std::string const & alias, std::unique_ptr<sf::Font> && f, bool is_fallback);

public: // static
    static std::vector<std::string> embedded_fonts ();

    /**
     * Load font from file
     */
    static bool load (std::string const & font_alias, pfs::filesystem::path const & path, bool is_fallback = false);

    /**
     * Load font from memory
     */
    static bool load (std::string const & font_alias, bool is_fallback = false);

    /**
     * Load fallback font from memory
     */
    static bool load ();

    /**
     * Get font by alias
     */
    static font get (std::string const & font_alias, font fallback_font = static_fallback_font);

    /**
     * Get default (fallback) font
     */
    static font get ()
    {
        return static_fallback_font;
    }
};

}} // namespace griotte::SFML
