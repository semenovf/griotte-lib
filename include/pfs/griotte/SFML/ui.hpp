////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.13 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <griotte/color.hpp>
#include <griotte/layout.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace sf {
class Event;
class RenderWindow;
}

namespace griotte {
namespace SFML {

class ui
{
public:
    struct options
    {
        int x, y;
        unsigned int w, h;
        std::string title;
        unsigned int antialiasing_level {8};
        unsigned int depth_bits {24};
    };

private:
    std::unique_ptr<sf::RenderWindow> _win;
    bool _running {true};
    bool _update_required {true};

    unsigned int _win_w {0};
    unsigned int _win_h {0};

    color_t _color {255, 255, 255, 255}; // background color
    std::unique_ptr<layout> _root_layout;

private:
    void step (sf::Event * ev);

public:
    ui (options && opts);
    ~ui ();

    void set_color (color_t value);

    template <typename L, typename ...Args>
    L & acquire_layout (Args &&... args)
    {
        auto ptr = new L(std::forward<Args>(args)...);
        _root_layout.reset(ptr);
        return *ptr;
    }

    unsigned int width () const noexcept;
    unsigned int height () const noexcept;

    unit_t width_units () const noexcept
    {
        return static_cast<unit_t>(width());
    }

    unit_t height_units () const noexcept
    {
        return static_cast<unit_t>(height());
    }

    void step ();
    void run ();
};

}} // namespace griotte::SFML
