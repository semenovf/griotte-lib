////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.15 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "item.hpp"
#include <memory>

namespace griotte {

class layout: public item
{
public:
    layout (): item () {}
    virtual ~layout () = default;

    template <typename T, typename ...Args>
    T & create (Args &&... args)
    {
        auto ptr = new T(std::forward<Args>(args)...);
        this->add_child(ptr);
        return *ptr;
    }

    void render (renderer_ptr_t r) override;

    virtual void update () = 0;
};

} // namespace griotte
