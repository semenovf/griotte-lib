////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.09 Initial version
////////////////////////////////////////////////////////////////////////////////

// * Do not include the OpenGL header yourself, as GLFW does this for you in a
//   platform-independent way
// * Do not include windows.h or other platform-specific headers unless you plan
//   on using those APIs yourself
// * If you do need to include such headers, include them before the GLFW header
//   and it will detect this

#include "pfs/fmt.hpp"
#include <GLFW/glfw3.h>
#include <functional>

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

            // By default, the OpenGL context GLFW creates may have any version.
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

private:
    static std::function<void (int, char const *)> errorHandler;
    static std::function<void (GLFWwindow * /*window*/
            , int /*key*/
            , int /*scancode*/
            , int /*action*/
            , int /*modsint*/)> keyHandler;

    static void error_callback (int error, char const * description)
    {
        Application::errorHandler(error, description);
    }

    static void key_callback (GLFWwindow * window
            , int key
            , int scancode
            , int action
            , int mods)
    {
        Application::keyHandler(window, key, scancode, action, mods);
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

int main ()
{
    Application app;

    return app.run( [] {
        // Create a windowed mode window and its OpenGL context
        GLFWwindow * window = glfwCreateWindow(1280, 960, "Hello World"
                , nullptr, nullptr);

        if (!window)
            return -1;

        Application::setKeyHandler(window, [] (GLFWwindow * window
                , int key
                , int scancode
                , int action
                , int mods) {

            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        });

        fmt::print("Press ESC to close window (and thus quit application) ...\n");

        // Before you can use the OpenGL API, you must have a current OpenGL
        // context. The context will remain current until you make another
        // context current or until the window owning the current context is
        // destroyed.
        // Make the window's context current.
        glfwMakeContextCurrent(window);

        while (!glfwWindowShouldClose(window)) {
            // Render here
            glClear(GL_COLOR_BUFFER_BIT);

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }

        if (window) {
            glfwDestroyWindow(window);
            window = nullptr;
        }

        return 0;
    });
}
