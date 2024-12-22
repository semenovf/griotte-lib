////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.12.19 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "align.hpp"
#include "layout.hpp"
#include "unit.hpp"
// #include <cstddef>
// #include <cstdint>
// #include <type_traits>
// #include <vector>

namespace griotte {

enum class orientation { horizontal, vertical };

class linear_layout: public layout
{
private:
    struct elem
    {
        int alignment;
    };

private:
    orientation _orient {orientation::horizontal};

public:
    linear_layout (orientation orient);
    ~linear_layout ();

public:
    template <typename T, typename ...Args>
    typename std::enable_if<std::is_base_of<item, T>::value, T>::type &
    create (Args &&... args)
    {
        static_assert(sizeof(T) > 0, "");

        struct tmp { elem a; char data[sizeof(T)]; };

        auto raw = new char [sizeof(tmp)];
        new (raw) elem;

        auto ptr = new (raw + offsetof(tmp, data)) T(std::forward<Args>(args)...);
        this->add_child(ptr, raw); // Add child node and save pointer

        return *ptr;
    }

    void update () override;
};

} // namespace griotte

