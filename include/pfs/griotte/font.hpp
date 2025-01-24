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
#include <string>
#include <vector>

namespace griotte {

class font
{
public:
    class impl;

private:
    impl * _d {nullptr};

private:
    font (impl * d);

public:
    font () = default;
    ~font () = default;

public:
    operator bool () const noexcept;

    void * native ();

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
    static font get (std::string const & font_alias, font fallback_font);
    static font get (std::string const & font_alias);

    /**
     * Get default (fallback) font
     */
    static font get ();
};

} // namespace griotte
