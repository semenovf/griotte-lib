////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024-2025 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.19 Initial version.
//      2025.08.21 Refused to use PIMPL idiom.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <pfs/filesystem.hpp>
#include <string>
#include <vector>

namespace griotte {

class font_t
{
private:
    std::string _alias;

public:
    /**
     * Constructs empty font.
     */
    font_t ();

    font_t (std::string const & alias);

    font_t (font_t const &) = default;
    font_t (font_t &&) noexcept = default;
    font_t & operator = (font_t const &) = default;
    font_t & operator = (font_t &&) noexcept = default;

    ~font_t () = default;

public:
    std::string const & alias () const noexcept
    {
        return _alias;
    }

public: // static
    /**
     * Returns aliases of embedded and loaded fonts.
     */
    static std::vector<std::string> fonts_available ();

    /**
     * Returns aliases of loaded fonts.
     */
    static std::vector<std::string> fonts_loaded ();

    /**
     * Load font from file
     */
    static bool load (std::string const & font_alias, pfs::filesystem::path const & path, bool is_fallback = false);

    /**
     * Load font from memory
     */
    static bool load (std::string const & font_alias, bool is_fallback = false);

    /**
     * Get font by alias.
     *
     * @return Specified font or a fallback font if the first is not found.
     */
    static font_t get (std::string const & font_alias);

    /**
     * Get default (fallback) font
     */
    static font_t get ();
};

} // namespace griotte
