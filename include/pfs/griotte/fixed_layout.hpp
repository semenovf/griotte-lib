////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.16 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "layout.hpp"

namespace griotte {

class fixed_layout: public layout
{
public:
    fixed_layout () = default;
    ~fixed_layout () = default;

    void update () override;
};

} // namespace griotte

