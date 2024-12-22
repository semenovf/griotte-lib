////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.15 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "direction.hpp"
#include "item.hpp"
#include <memory>
#include <type_traits>

namespace griotte {

class layout: public item
{
protected:
    unit_t _margins[4];

public:
    layout ();
    virtual ~layout ();

    template <typename T, typename ...Args>
    typename std::enable_if<std::is_base_of<item, T>::value, T>::type &
    create (Args &&... args)
    {
        auto ptr = new T(std::forward<Args>(args)...);
        this->add_child(ptr, ptr);
        return *ptr;
    }

    void set_margins (unit_t margins[4]);
    void set_margin (direction dir, unit_t value);

    void render (renderer_ptr_t r) override;

    virtual void update () = 0;
};

} // namespace griotte
