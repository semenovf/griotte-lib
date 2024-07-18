////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.18 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "griotte/logger.hpp"
#include <pfs/log.hpp>

namespace griotte {

static constexpr char const * TAG = "griotte";

static void d (std::string const & text)
{
    LOGD(TAG, "{}", text);
}

static void i (std::string const & text)
{
    LOGI(TAG, "{}", text);
}

static void w (std::string const & text)
{
    LOGW(TAG, "{}", text);
}

static void e (std::string const & text)
{
    LOGE(TAG, "{}", text);
}

void (* logger::d) (std::string const &) = griotte::d; // NOTE assigment to self without prefixed with griotte
void (* logger::i) (std::string const &) = griotte::i; // NOTE assigment to self without prefixed with griotte
void (* logger::w) (std::string const &) = griotte::w; // NOTE assigment to self without prefixed with griotte
void (* logger::e) (std::string const &) = griotte::e; // NOTE assigment to self without prefixed with griotte

} // namespace griotte
