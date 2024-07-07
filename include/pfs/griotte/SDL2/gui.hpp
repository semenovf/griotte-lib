////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.07 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

union SDL_Event;
struct SDL_Window;
struct SDL_Renderer;

namespace griotte {
namespace SDL2 {

class gui
{
public:
    struct options
    {
        int x, y, w, h;
        std::string title;
    };

private:
    SDL_Window * _win {nullptr};
    SDL_Renderer * _r {nullptr};
    bool _running {true};
    bool _update_required {true};

    int _win_w {0};
    int _win_h {0};

private:
    void step (SDL_Event * ev);

public:
    gui (options && opts);
    ~gui ();

    void step ();
    void run ();
};

}} // namespace griotte::SDL2

