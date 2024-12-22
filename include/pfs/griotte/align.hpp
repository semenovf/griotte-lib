////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.12.22 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <cstdint>

namespace griotte {

struct align
{
    enum value_type: int {
        // Horizontal alignment
          left    = 0x0001 ///< Aligns with the left edge.
        , right   = 0x0002 ///< Aligns with the right edge.
        , hcenter = 0x0004 ///< Centers horizontally in the available space.
        , justify = 0x0008 ///< Justifies the text in the available space.

        // Vertical alignment
        , top      = 0x0020 ///< Aligns with the top.
        , bottom   = 0x0040 ///< Aligns with the bottom.
        , vcenter  = 0x0080 ///< Centers vertically in the available space.
        , baseline = 0x0100 ///< Aligns with the baseline.

        , center   = hcenter | vcenter ///< Centers in both dimensions.
    };

    int value;
};

} // namespace griotte


