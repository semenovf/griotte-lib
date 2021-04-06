////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.18 Initial version
////////////////////////////////////////////////////////////////////////////////
#include "pfs/fmt.hpp"
#include <GLFW/glfw3.h>
#include <functional>

// * Do not include the OpenGL header yourself, as GLFW does this for you in a
//   platform-independent way
// * Do not include windows.h or other platform-specific headers unless you plan
//   on using those APIs yourself
// * If you do need to include such headers, include them before the GLFW header
//   and it will detect this

//
// Source: https://www.glfw.org/documentation.html
//

class Application
{
public:
    /**
     * @brief Creates default application instance
     */
    Application ()
    {
        if (glfwInit()) {
            _initialized = true;
        }

        // Default error handler
        setErrorHandler([] (int error, char const * description) {
            fmt::print("ERROR {}: {}\n", error, description);
        });
    }

    /**
     * @brief Creates application instance with minimal requirements for OpenQL
     *        version
     */
    Application (int minOpenGlMajorVersion, int minOpenGlMinorVersion = 0)
        : Application()
    {
        if (minOpenGlMajorVersion > 0) {
            if (minOpenGlMinorVersion < 0) {
                minOpenGlMinorVersion = 0;
            }

            // By default, the OpenGL context GLFW may have any version.
            // You can require a minimum OpenGL version by setting the
            // GLFW_CONTEXT_VERSION_MAJOR and GLFW_CONTEXT_VERSION_MINOR hints
            // before creation
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, minOpenGlMajorVersion);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minOpenGlMinorVersion);
        }
    }

    ~Application ()
    {
        glfwTerminate();
    }

    bool good () const
    {
        return _initialized;
    }

    template <typename ApplicationLoop>
    int run (ApplicationLoop && loop)
    {
        int result = 0;

        if (_initialized) {
            result = loop();
        }

        return result;
    }

public:
    template <typename ErrorHandler>
    static void setErrorHandler (ErrorHandler && handler)
    {
        errorHandler = std::forward<ErrorHandler>(handler);
        glfwSetErrorCallback(error_callback);
    }

    template <typename KeyHandler>
    static void setKeyHandler (GLFWwindow * window, KeyHandler && handler)
    {
        if (window) {
            keyHandler = std::forward<KeyHandler>(handler);
            glfwSetKeyCallback(window, key_callback);
        }
    }

    template <typename FramebufferSizeHandler>
    static void setFramebufferSizeHandler (GLFWwindow * window
            , FramebufferSizeHandler && handler)
    {
        if (window) {
            framebufferSizeHandler = std::forward<FramebufferSizeHandler>(handler);
            glfwSetFramebufferSizeCallback(window, framebuffersize_callback);
        }
    }

    template <typename MonitorHandler>
    static void setMonitorHandler (MonitorHandler && handler)
    {
        monitorHandler = std::forward<MonitorHandler>(handler);
        glfwSetMonitorCallback(monitor_callback);
    }

private:
    static std::function<void (int, char const *)> errorHandler;
    static std::function<void (GLFWwindow * /*window*/
            , int /*key*/
            , int /*scancode*/
            , int /*action*/
            , int /*modsint*/)> keyHandler;
    static std::function<void (GLFWwindow * /*window*/
            , int /*width*/
            , int /*height*/)> framebufferSizeHandler;

    static std::function<void (GLFWmonitor * /*monitor*/
            , int /*event*/)> monitorHandler;

    static void error_callback (int error, char const * description)
    {
        errorHandler(error, description);
    }

    static void key_callback (GLFWwindow * window
            , int key
            , int scancode
            , int action
            , int mods)
    {
        keyHandler(window, key, scancode, action, mods);
    }

    static void framebuffersize_callback (GLFWwindow * window
            , int width
            , int height)
    {
        framebufferSizeHandler(window, width, height);
    }

    static void monitor_callback (GLFWmonitor * monitor, int event)
    {
        monitorHandler(monitor, event);
    }

private:
    bool _initialized {false};
};

std::function<void (int, char const *)> Application::errorHandler;
std::function<void (GLFWwindow * /*window*/
        , int /*key*/
        , int /*scancode*/
        , int /*action*/
        , int /*modsint*/)> Application::keyHandler;

std::function<void (GLFWwindow * /*window*/
        , int /*width*/
        , int /*height*/)> Application::framebufferSizeHandler {[] (
                  GLFWwindow * /*window*/
                , int width
                , int height) {
                    // By defualt rearranges OpenGL viewport to the current
                    // framebuffer size.
                    glViewport(0, 0, width, height);
                }};

std::function<void (GLFWmonitor * /*monitor*/
            , int /*event*/)> Application::monitorHandler;
