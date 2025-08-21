////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.07 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <pfs/numeric_cast.hpp>
#include <cstdint>

namespace griotte {

class rgba_color final
{
    std::uint8_t _alpha;
    std::uint8_t _red;
    std::uint8_t _green;
    std::uint8_t _blue;

public:
    /**
     * Constructs transparent color.
     */
    constexpr rgba_color () noexcept
        : _alpha(0)
        , _red(0)
        , _green(0)
        , _blue(0)
    {}

    constexpr rgba_color (int red, int green, int blue, int alpha = 255) noexcept
        : _alpha(pfs::numeric_cast<std::uint8_t>(alpha))
        , _red(pfs::numeric_cast<std::uint8_t>(red))
        , _green(pfs::numeric_cast<std::uint8_t>(green))
        , _blue(pfs::numeric_cast<std::uint8_t>(blue))
    {}

    rgba_color (rgba_color const & rhs) = default;
    rgba_color & operator = (rgba_color const & rhs) = default;

    constexpr std::uint8_t alpha () const noexcept { return _alpha; }
    constexpr std::uint8_t red ()   const noexcept { return _red; }
    constexpr std::uint8_t green () const noexcept { return _green; }
    constexpr std::uint8_t blue ()  const noexcept { return _blue; }

    constexpr bool is_transparent () const noexcept { return _alpha == 0; }
};

using color_t = rgba_color;

} // namespace griotte
