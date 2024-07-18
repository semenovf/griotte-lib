////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.07 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "griotte/SDL2/gui.hpp"
#include <pfs/i18n.hpp>
#include <pfs/log.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <stdexcept>

namespace griotte {
namespace SDL2 {

static constexpr int FIRST_SUPPORTED_DRIVER_INDEX = -1;

gui::gui (options && opts)
{
    Uint32 required_subsystems = 0;

    if (!(SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO))
        required_subsystems |= SDL_INIT_VIDEO;

    if (!(SDL_WasInit(SDL_INIT_EVENTS) & SDL_INIT_EVENTS))
        required_subsystems |= SDL_INIT_EVENTS;

    if (!(SDL_WasInit(SDL_INIT_TIMER) & SDL_INIT_TIMER))
        required_subsystems |= SDL_INIT_TIMER;

    int rc = SDL_Init(required_subsystems);

    if (rc < 0)
        throw std::runtime_error(tr::f_("SDL could not be initialize: {}", SDL_GetError()));

    Uint32 windowFlags = SDL_WINDOW_SHOWN
        | SDL_WINDOW_RESIZABLE
        | SDL_WINDOW_MOUSE_CAPTURE
        | SDL_WINDOW_OPENGL; // If not set window will be recreated in SDL_CreateRenderer() call

    // Create window
    _win = SDL_CreateWindow(opts.title.c_str(), opts.x, opts.y, opts.w, opts.h, windowFlags);

    if (_win == nullptr) {
        SDL_Quit();
        throw std::runtime_error(tr::f_("SDL_CreateWindow faild: {}", SDL_GetError()));
    }

    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    _r = SDL_CreateRenderer(_win, FIRST_SUPPORTED_DRIVER_INDEX, rendererFlags);

    if (_r == nullptr) {
        SDL_DestroyWindow(_win);
        SDL_Quit();
        throw std::runtime_error(tr::f_("SDL_CreateRenderer failed: {}", SDL_GetError()));
    }

    SDL_GetWindowSize(_win, & _win_w, & _win_h);
}

gui::~gui ()
{
    // Destroy renderer
    if (_r != nullptr)
        SDL_DestroyRenderer(_r);

    _r = nullptr;

    // Destroy window
    if (_win != nullptr)
        SDL_DestroyWindow(_win);

    _win = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

void gui::step (SDL_Event * ev)
{
    switch (ev->type) {
        case SDL_QUIT:
            _running = false;
            break;

        case SDL_WINDOWEVENT:
            switch (ev->window.event) {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    _win_w = ev->window.data1;
                    _win_h = ev->window.data2;
                    LOG_TRACE_1("SDL_WINDOWEVENT_SIZE_CHANGED: {}x{}", _win_w, _win_h);
                    break;

                case SDL_WINDOWEVENT_RESIZED:
                    LOG_TRACE_1("SDL_WINDOWEVENT_RESIZED: {}x{}", ev->window.data1, ev->window.data2);
                    _update_required = true;
                    break;

                case SDL_WINDOWEVENT_MINIMIZED:
                    LOG_TRACE_1("SDL_WINDOWEVENT_MINIMIZED");
                    _update_required = true;
                    break;

                // After SDL_WINDOWEVENT_MAXIMIZED, fired SDL_WINDOWEVENT_RESIZED event with actual window size
                case SDL_WINDOWEVENT_MAXIMIZED:
                    LOG_TRACE_1("SDL_WINDOWEVENT_MAXIMIZED");
                    _update_required = true;
                    break;

                // Before SDL_WINDOWEVENT_RESTORED, fired SDL_WINDOWEVENT_RESIZED event with actual window size
                case SDL_WINDOWEVENT_RESTORED:
                    LOG_TRACE_1("SDL_WINDOWEVENT_RESTORED");
                    _update_required = true;
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }
}

void gui::step ()
{
    SDL_Event ev;

    while (SDL_PollEvent(& ev))
        step(& ev);

    // FIXME Implement useful rendering
    if (_update_required) {
        LOG_TRACE_1("UPDATE REQUIRED");

        SDL_SetRenderDrawColor(_r, 0xdf, 0xfa, 0xec, 255);
        SDL_RenderClear(_r);

        SDL_SetRenderDrawColor(_r, 0x00, 0x00, 0x00, 255);
        SDL_RenderDrawLine(_r, 0, 0, _win_w - 1, _win_h - 1);
        SDL_RenderDrawLine(_r, _win_w - 1, 0, 0, _win_h - 1);

        SDL_Rect rect1 {_win_w / 2 - 100, _win_h / 2 - 100, 200, 200};
        SDL_RenderDrawRect(_r, & rect1);

        SDL_SetRenderDrawColor(_r, 0xff, 0xff, 0x00, 255);
        SDL_Rect rect2 {_win_w / 2 - 50, _win_h / 2 - 50, 100, 100};
        SDL_RenderFillRect(_r, & rect2);

        SDL_RenderPresent(_r);
        _update_required = false;
    }
}

void gui::run ()
{
    // TODO Must be initialized with SDL_DisplayMode.refresh_rate value returned by
    // SDL_GetDesktopDisplayMode()
    float millis_per_frame = 1000.0 / 60.0;

    while (_running) {
        auto start_frame = SDL_GetTicks();
        step();
        auto end_frame = SDL_GetTicks();

        /* figure out how much time we have left, and then sleep */

        auto remain_millis = millis_per_frame - (end_frame - start_frame);

        if (remain_millis < 0) {
            remain_millis = 0;
        } else if (remain_millis > millis_per_frame) {
            remain_millis = millis_per_frame;
        }

        if (remain_millis > 0) {
            SDL_ClearError();
            SDL_Event ev;
            auto rc = SDL_WaitEventTimeout(& ev, remain_millis);

            // An error or the timeout elapsed without an event arriving
            if (rc == 0) {
                char const * errstr = SDL_GetError();

                // Timeout elapsed
                if (errstr[0] == '\x0') {
                    ;
                } else {
                    throw std::runtime_error(tr::f_("SDL_WaitEventTimeout failed: {}", errstr));
                }
            } else {
                step(& ev);
            }
        }
    }
}

}} // namespace griotte::SDL2
