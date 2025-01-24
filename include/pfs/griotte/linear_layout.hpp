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
        unit_t margins[4];
        unit_t preferred_width;
        unit_t preferred_height;
        unit_t max_width;
        unit_t min_width;
        unit_t max_height;
        unit_t min_height;
    };

private:
    orientation _orient {orientation::horizontal};
    std::size_t _count {0}; // number of children

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
        int alignment = _orient == orientation::horizontal
            ? align::left : align::top;
        new (raw) elem {alignment, {0, 0, 0, 0}
            , -1.0f, -1.0f
            , -1.0f, -1.0f
            , -1.0f, -1.0f
        };

        auto ptr = new (raw + offsetof(tmp, data)) T(std::forward<Args>(args)...);
        this->add_child(ptr, raw); // Add child node and save pointer

        _count++;

        return *ptr;
    }

    void set_margins (item & i, unit_t margins[4]);
    void set_margins (item & i, unit_t margins);
    void set_margin (item & i, direction dir, unit_t value);

    void set_preferred_width (item & i, unit_t w);
    void set_preferred_height (item & i, unit_t h);

    void update () override;

private:
    elem * elem_cast (node *);
    elem * elem_cast (item *);
};

} // namespace griotte

