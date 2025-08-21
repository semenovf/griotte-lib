////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace griotte {

class font_style_t
{
    enum style_enum
    {
          regular     = 0 << 0 // regular characters, no style
        , bold        = 1 << 0
        , italic      = 1 << 1
        , underlined  = 1 << 2
        , strikeout   = 1 << 3
    };

    std::underlying_type<style_enum>::type _value {style_enum::regular};

public:
    font_style_t () = default;
    ~font_style_t () = default;

    /**
     * Clear all styles and set to regular.
     */
    void set_regular () noexcept
    {
        _value = style_enum::regular;
    }

    /**
     * Add bold style.
     */
    void set_bold () noexcept
    {
        _value |= style_enum::bold;
    }

    /**
     * Add italic style.
     */
    void set_italic () noexcept
    {
        _value |= style_enum::italic;
    }

    /**
     * Add underlined style.
     */
    void set_underlined () noexcept
    {
        _value |= style_enum::underlined;
    }

    /**
     * Add strikeout style.
     */
    void set_strikeout () noexcept
    {
        _value |= style_enum::strikeout;
    }

    bool is_regular () const noexcept
    {
        return _value == style_enum::regular;
    }

    bool is_bold () const noexcept
    {
        return _value & style_enum::bold;
    }

    bool is_italic () const noexcept
    {
        return _value & style_enum::italic;
    }

    bool is_underlined () const noexcept
    {
        return _value & style_enum::underlined;
    }

    bool is_strikeout () const noexcept
    {
        return _value & style_enum::strikeout;
    }
};

} // namespace griotte
