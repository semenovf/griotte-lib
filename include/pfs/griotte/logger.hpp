////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.18 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

namespace griotte {

struct logger
{
    static void (* d) (std::string const &);
    static void (* i) (std::string const &);
    static void (* w) (std::string const &);
    static void (* e) (std::string const &);
};

} // namespace griotte
