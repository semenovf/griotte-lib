////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.30 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "layout.hpp"
#include "unit.hpp"
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace griotte {

enum class anchor_spot
{
      none
    , left
    , top
    , right
    , bottom
    , horizontal_center
    , vertical_center
};

struct anchor_line
{
    item * rel {nullptr}; // relative to this object
    anchor_spot spot {anchor_spot::none};
    unit_t margin {0};
};

struct anchors
{
    // TODO anchors.alignWhenCentered : bool
    // TODO anchors.baseline : AnchorLine
    // TODO anchors.baselineOffset : real
    // TODO anchors.bottomMargin : real
    // TODO anchors.centerIn : Item
    // TODO anchors.fill : Item
    // TODO anchors.horizontalCenterOffset : real
    // TODO anchors.leftMargin : real
    // TODO anchors.margins : real
    // TODO anchors.rightMargin : real
    // TODO anchors.topMargin : real
    // TODO anchors.verticalCenterOffset : real

    unit_t width {0};
    unit_t height {0};
    anchor_line left;
    anchor_line top;
    anchor_line right;
    anchor_line bottom;
    anchor_line horizontal_center;
    anchor_line vertical_center;
};

class anchors_layout: public layout
{
private:
    struct elem
    {
        anchors a;
    };

public:
    anchors_layout () = default;
    ~anchors_layout ();

    template <typename T, typename ...Args>
    typename std::enable_if<std::is_base_of<item, T>::value, T>::type &
    create (Args &&... args)
    {
        static_assert(sizeof(T) > 0, "");

        struct tmp { anchors a; char data[sizeof(T)]; };

        auto raw = new char [sizeof(tmp)];
        new (raw) elem;

        auto ptr = new (raw + offsetof(tmp, data)) T(std::forward<Args>(args)...);
        this->add_child(ptr, raw); // Add child node and save pointer

        return *ptr;
    }

    void fill (item & i, item & rel);
    void set_width (item & i, unit_t w);
    void set_height (item & i, unit_t h);
    void set_left (item & i, item & rel, anchor_spot rel_spot, unit_t margin = 0);
    void set_top (item & i, item & rel, anchor_spot rel_spot, unit_t margin = 0);
    void set_right (item & i, item & rel, anchor_spot rel_spot, unit_t margin = 0);
    void set_bottom (item & i, item & rel, anchor_spot rel_spot, unit_t margin = 0);
    void set_margins (item & i, unit_t m);

    void update () override;
};

} // namespace griotte
