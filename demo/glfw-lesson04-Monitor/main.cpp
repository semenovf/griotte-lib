////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019-2020 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.25 Initial version
////////////////////////////////////////////////////////////////////////////////

#include "pfs/griotte/context.hpp"

#define INDENT_SPACE "    "

int main ()
{
    pfs::griotte::context app;

    if (!app.good()) {
        fmt::print("ERROR: {}", app.errorstr());
        return -1;
    }

    app.set_monitor_handler([] (GLFWmonitor * monitor, int event) {
        auto name = glfwGetMonitorName(monitor);
        switch(event) {
            case GLFW_CONNECTED:
                fmt::print("Monitor [{}] connected", name);
                break;
            case GLFW_DISCONNECTED:
                fmt::print("Monitor [{}] disconnected", name);
                break;
            default:
                break;
        }
    });

    GLFWmonitor * primaryMonitor = glfwGetPrimaryMonitor();

    int monitorCount {0};

    GLFWmonitor ** monitors = glfwGetMonitors(& monitorCount);

    fmt::print("Number of monitors connected: {}\n", monitorCount);
    fmt::print("Monitors: (* - primary)\n");

    for (int i = 0; i < monitorCount; i++) {
        auto m = monitors[i];
        bool isPrimary = (m == primaryMonitor);
        fmt::print("{} Monitor{:<2}:\n", (isPrimary ? "*" : " "), i);
        fmt::print(INDENT_SPACE "Name: {}\n", glfwGetMonitorName(m));

        // Physical size in millimetres of the display area of the monitor.
        // Some systems do not provide accurate monitor size information,
        // either because the monitor EDID data is incorrect or because the
        // driver does not report it accurately
        int widthMM {0};
        int heightMM {0};
        glfwGetMonitorPhysicalSize (m, & widthMM, & heightMM);
        fmt::print(INDENT_SPACE "Physical size: {}mm x {}mm\n", widthMM, heightMM);

        // Content scale for the specified monitor.
        // The content scale is the ratio between the current DPI and the
        // platform's default DPI.
        // The content scale may depend on both the monitor resolution and pixel
        // density and on user settings. It may be very different from the raw
        // DPI calculated from the physical size and current resolution.
        float xscale;
        float yscale;
        glfwGetMonitorContentScale (m, & xscale, & yscale);
        fmt::print(INDENT_SPACE "Content scale: {} x {}\n", xscale, yscale);

        // Position of the monitor's viewport on the virtual screen
        int xpos {0};
        int ypos {0};
        glfwGetMonitorPos(m, & xpos, & ypos);
        fmt::print(INDENT_SPACE "Position: {{{}, {}}}\n", xpos, ypos);

        // The work area of the monitor
        {
            int xpos {0};
            int ypos {0};
            int width {0};
            int height {0};
            glfwGetMonitorWorkarea(m, & xpos, & ypos, & width, & height);
            fmt::print(INDENT_SPACE "Work area: {{{}, {}, {} x {}}}\n"
                    , xpos, ypos, width, height);
        }

    {
        // The available video modes for the specified monitor
        int count {0};
        GLFWvidmode const * vidmodes = glfwGetVideoModes(m, & count);
        GLFWvidmode const * currentVidmode = glfwGetVideoMode(m);
        fmt::print(INDENT_SPACE "Video modes available: {}\n", count);

        for (int i = 0; i < count; i++) {
            bool isCurrentVidmode = (
                       currentVidmode->width == vidmodes[i].width
                    && currentVidmode->height == vidmodes[i].height
                    && currentVidmode->refreshRate == vidmodes[i].refreshRate
                    && currentVidmode->redBits == vidmodes[i].redBits
                    && currentVidmode->greenBits == vidmodes[i].greenBits
                    && currentVidmode->blueBits == vidmodes[i].blueBits);

            fmt::print(INDENT_SPACE INDENT_SPACE "{}{} x {} {}Hz r({}) g({}) b({})\n"
                    , (isCurrentVidmode ? '*' : ' ')
                    , vidmodes[i].width
                    , vidmodes[i].height
                    , vidmodes[i].refreshRate
                    , vidmodes[i].redBits
                    , vidmodes[i].greenBits
                    , vidmodes[i].blueBits);
        }
    }

    // Generates a gamma ramp and sets it for the specified monitor
    // void glfwSetGamma (GLFWmonitor *monitor, float gamma)

    // Returns the current gamma ramp for the specified monitor
    // const GLFWgammaramp * glfwGetGammaRamp (GLFWmonitor *monitor)

    // void glfwSetGammaRamp (GLFWmonitor *monitor, const GLFWgammaramp *ramp)
    }

    return app.run( [] {
        // Create a windowed mode window and its OpenGL context
        GLFWwindow * window = glfwCreateWindow(1, 1, "Lesson 04", nullptr, nullptr);

        if (!window)
            return -1;

        // Before you can use the OpenGL API, you must have a current OpenGL
        // context. The context will remain current until you make another
        // context current or until the window owning the current context is
        // destroyed.
        // Make the window's context current.
        glfwMakeContextCurrent(window);

        if (window) {
            glfwDestroyWindow(window);
            window = nullptr;
        }

        return 0;
    });
}
