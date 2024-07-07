////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.06 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include <griotte/SDL2/gui.hpp>
#include <pfs/fmt.hpp>
#include <pfs/log.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <cstdlib>

static constexpr char const * TAG = "SDL2-demo";
static constexpr int SCREEN_WIDTH = 640;
static constexpr int SCREEN_HEIGHT = 480;

// static void updateSurface (SDL_Window & window, SDL_Surface * & screenSurface)
// {
//     if (screenSurface != nullptr) {
//         SDL_DestroyWindowSurface(& window);
//         screenSurface = nullptr;
//     }
//
//     // Get window surface
//     screenSurface = SDL_GetWindowSurface(& window);
//
//     // Fill the surface white
//     SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xcc, 0xcc, 0xcc));
//
//     // Update the surface
//     SDL_UpdateWindowSurface(& window);
// }

static std::string stringify_pixel_format (std::uint32_t f)
{
    std::string result = fmt::format("{} (bits per pixel: {})", SDL_GetPixelFormatName(f), SDL_BITSPERPIXEL(f));
    return result;
}

static bool dump_display_mode ()
{
    auto displayCount = SDL_GetNumVideoDisplays();

    if (displayCount < 0) {
        LOGE(TAG, "SDL_GetNumVideoDisplays failed: {}", SDL_GetError());
        return false;
    }

    LOGD(TAG, "Number of displays: {}", displayCount);

    for (decltype(displayCount) i = 0; i < displayCount; i++) {

        SDL_DisplayMode dm;

        auto rc = SDL_GetDesktopDisplayMode(i, & dm);

        if (rc < 0) {
            LOGE(TAG, "SDL_GetDesktopDisplayMode failed: {}", SDL_GetError());
            return false;
        }

        LOGD(TAG, "Desktop display mode for display {{{}}}", i);
        LOGD(TAG, "\tformat      : {}", stringify_pixel_format(dm.format));
        LOGD(TAG, "\tsize        : {}x{}", dm.w, dm.h);
        LOGD(TAG, "\trefresh_rate: {} 1/s", dm.refresh_rate);

        auto displayModeCount = SDL_GetNumDisplayModes(i);

        if (displayModeCount < 1) {
            LOGE(TAG, "SDL_GetNumDisplayModes failed: {}", SDL_GetError());
            return false;
        }

        LOGD(TAG, "Number of modes for display {{{}}}: {}", i, displayModeCount);

        for (decltype(displayModeCount) k = 0; k < displayModeCount; k++) {
            auto rc = SDL_GetDisplayMode(i, k, & dm);

            if (rc < 0) {
                LOGE(TAG, "SDL_GetDisplayMode({}, {}) failed: {}", i, k, SDL_GetError());
                return false;
            }

            LOGD(TAG, "SDL Display mode for display {{{}}} and mode {{{}}}", i, k);
            LOGD(TAG, "\tformat      : {}", stringify_pixel_format(dm.format));
            LOGD(TAG, "\tsize        : {}x{}", dm.w, dm.h);
            LOGD(TAG, "\trefresh_rate: {} 1/s", dm.refresh_rate);
                // void *driverdata;           /**< driver-specific data, initialize to 0 */
        }
    }

    return true;
}

int main ([[maybe_unused]] int argc, [[maybe_unused]] char * argv[])
{
    griotte::SDL2::gui gui { griotte::SDL2::gui::options {
          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT
        , "SDL2 Demo"
    }};

    gui.run();

#if __COMMENT__
    constexpr int FIRST_SUPPORTED_DRIVER_INDEX = -1;

    // Initialize SDL
    // SDL_INIT_VIDEO activates SDL_INIT_EVENTS automatically, but let's do it explicitly
    // int rc = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    int rc = SDL_Init(SDL_INIT_EVERYTHING);

    if (rc < 0) {
        LOGE(TAG, "SDL could not initialize: {}", SDL_GetError());
        return EXIT_FAILURE;
    }

    // if (!dump_display_mode())
    //     return EXIT_FAILURE;

    Uint32 windowFlags = SDL_WINDOW_RESIZABLE
        | SDL_WINDOW_MOUSE_CAPTURE
        | SDL_WINDOW_OPENGL
        | SDL_WINDOW_SHOWN;

    // Create window
    SDL_Window * window = SDL_CreateWindow("SDL2 Window title"
        , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
        , SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if (window == nullptr) {
        LOGE(TAG, "SDL_CreateWindow faild: {}", SDL_GetError());
        return EXIT_FAILURE;
    }

    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer * renderer = SDL_CreateRenderer(window, FIRST_SUPPORTED_DRIVER_INDEX, rendererFlags);

    // if (renderer == nullptr) {
    //     LOGE(TAG, "SDL_CreateRenderer failed: {}", SDL_GetError());
    //     return EXIT_FAILURE;
    // }


    // SDL_Surface * screenSurface = nullptr;

    // updateSurface(*window, screenSurface);

    SDL_Event e;
    bool running = true;
    bool updateRequired = true;

    while (running) {
        auto hasPendingEvents = SDL_PollEvent(& e) == 1;

        if (hasPendingEvents) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_WINDOWEVENT:
                    switch (e.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                            LOGD(TAG, "SDL_WINDOWEVENT_RESIZED: {}x{}", e.window.data1, e.window.data2);
                            // updateSurface(*window, screenSurface);
                            updateRequired = true;
                            break;

                        case SDL_WINDOWEVENT_MINIMIZED:
                            LOGD(TAG, "SDL_WINDOWEVENT_MINIMIZED");
                            updateRequired = true;
                            break;

                        // After SDL_WINDOWEVENT_MAXIMIZED, fired SDL_WINDOWEVENT_RESIZED event with actual window size
                        case SDL_WINDOWEVENT_MAXIMIZED:
                            LOGD(TAG, "SDL_WINDOWEVENT_MAXIMIZED");
                            updateRequired = true;
                            break;

                        // Before SDL_WINDOWEVENT_RESTORED, fired SDL_WINDOWEVENT_RESIZED event with actual window size
                        case SDL_WINDOWEVENT_RESTORED:
                            LOGD(TAG, "SDL_WINDOWEVENT_RESTORED");
                            updateRequired = true;
                            break;

                        default:
                            break;
                    }

                    break;

                default:
                    break;
            }
        } else {
            // SDL_WaitEventTimeout(& e, 10); // wait 10 milliseconds
        }

        // if (updateRequired) {
        //     LOGD(TAG, "UPDATE REQUIRED");
        //
        //     SDL_SetRenderDrawColor(renderer, 0xdf, 0xfa, 0xec, 255);
        //     SDL_RenderClear(renderer);
        //
        //     SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
        //     SDL_RenderDrawLine(renderer, 0, 0, 200, 200);
        //
        //     SDL_Rect rect1 {100, 100, 200, 200};
        //     SDL_RenderDrawRect(renderer, & rect1);
        //
        //     SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 255);
        //     SDL_Rect rect2 {150, 150, 100, 100};
        //     SDL_RenderFillRect(renderer, & rect2);
        //
        //     SDL_RenderPresent(renderer);
        //     updateRequired = false;
        // }
    }

    // Destroy renderer
    // SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

#endif
    return EXIT_SUCCESS;
}
