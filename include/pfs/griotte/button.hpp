////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.07 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "item.hpp"

namespace griotte {

class button: public item
{
public:
    button () = default;
    ~button () = default;
};

} // namespace griotte

