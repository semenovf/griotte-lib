////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.26 Initial version
////////////////////////////////////////////////////////////////////////////////
#include "pfs/fmt.hpp"
#include "pfs/griotte/font.hpp"
#include "GLFW/glfw3.h"
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
namespace pfs {
namespace griotte {

template <typename dummy>
struct context_static_members
{
    static std::function<void (int, char const *)> error_handler;
    static std::function<void (GLFWwindow * /*window*/
            , int /*key*/
            , int /*scancode*/
            , int /*action*/
            , int /*modsint*/)> key_handler;
    static std::function<void (GLFWwindow * /*window*/
            , int /*width*/
            , int /*height*/)> framebuffer_size_handler;

    static std::function<void (GLFWmonitor * /*monitor*/
            , int /*event*/)> monitor_handler;
};

class context : public context_static_members<int>
{
public:
    /**
     * @brief Creates default application instance
     */
    context ()
    {
        if (!glfwInit()) {
            _errorstr = "GLFW library initialization failed";
            return;
        }

        auto is_error = FT_Init_FreeType(& _font_library);

        if (is_error) {
            _errorstr = "Freetype library initialization failed";
            return;
        }

        // Default GLFW error handler
        set_error_handler([this] (int error, char const * description) {
            _errorstr = fmt::format("{}: {}", error, description);
            fmt::print("ERROR {}\n", _errorstr);
        });

        _initialized = true;
    }

    /**
     * @brief Creates application instance with minimal requirements for OpenQL
     *        version
     */
    context (int min_open_gl_major_version, int min_open_gl_minor_version = 0)
        : context()
    {
        if (min_open_gl_major_version > 0) {
            if (min_open_gl_minor_version < 0) {
                min_open_gl_minor_version = 0;
            }

            // By default, the OpenGL context GLFW creates may have any version.
            // You can require a minimum OpenGL version by setting the
            // GLFW_CONTEXT_VERSION_MAJOR and GLFW_CONTEXT_VERSION_MINOR hints
            // before creation
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, min_open_gl_major_version);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min_open_gl_minor_version);
        }

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    ~context ()
    {
        FT_Done_FreeType(_font_library);
        glfwTerminate();
    }

    bool good () const
    {
        return _initialized;
    }

    template <typename Loop>
    int run (Loop && loop)
    {
        int result = 0;

        if (_initialized) {
            result = loop();
        }

        return result;
    }

    std::string const & errorstr () const
    {
        return _errorstr;
    }


    /**
     * @return number of faces in font file or -1 if error occured
     */
    int font_faces_count (std::string const & path)
    {
        FT_Face face {nullptr};

        auto ec = FT_New_Face(_font_library
            , path.c_str()
            , -1 // Request for font face count in the file
            , & face);

        if (ec)
            return -1;

        int n = face->num_faces;
        FT_Done_Face(face);

        return n;
    }

    font load_font (std::string const & path)
    {
        return load_font(path, 0);
    }

    font load_font (std::string const & path, int face_index)
    {
        FT_Face face {nullptr};

        auto ec = FT_New_Face(_font_library
            , path.c_str()
            , face_index
            , & face );

        if (ec == FT_Err_Unknown_File_Format) {
            // The font file could be opened and read, but it appears
            // that its font format is unsupported.
            _errorstr = "unknown font file format";
            return font{};
        } else if (ec) {
            // Another error code means that the font file could not
            // be opened or read, or that it is broken.
            _errorstr = "unable to load font from file, file may be broken";
            return font{};
        }

        return font{face};
    }

public:
    template <typename ErrorHandler>
    static void set_error_handler (ErrorHandler && handler)
    {
        error_handler = std::forward<ErrorHandler>(handler);
        glfwSetErrorCallback(error_callback);
    }

    template <typename KeyHandler>
    static void set_key_handler (GLFWwindow * window, KeyHandler && handler)
    {
        if (window) {
            key_handler = std::forward<KeyHandler>(handler);
            glfwSetKeyCallback(window, key_callback);
        }
    }

    template <typename FramebufferSizeHandler>
    static void set_framebuffer_size_handler (GLFWwindow * window
            , FramebufferSizeHandler && handler)
    {
        if (window) {
            framebuffer_size_handler = std::forward<FramebufferSizeHandler>(handler);
            glfwSetFramebufferSizeCallback(window, framebuffersize_callback);
        }
    }

    template <typename MonitorHandler>
    static void set_monitor_handler (MonitorHandler && handler)
    {
        monitor_handler = std::forward<MonitorHandler>(handler);
        glfwSetMonitorCallback(monitor_callback);
    }

private:
    static void error_callback (int error, char const * description)
    {
        error_handler(error, description);
    }

    static void key_callback (GLFWwindow * window
            , int key
            , int scancode
            , int action
            , int mods)
    {
        key_handler(window, key, scancode, action, mods);
    }

    static void framebuffersize_callback (GLFWwindow * window
            , int width
            , int height)
    {
        framebuffer_size_handler(window, width, height);
    }

    static void monitor_callback (GLFWmonitor * monitor, int event)
    {
        monitor_handler(monitor, event);
    }

private:
    bool _initialized {false};
    std::string _errorstr;
    FT_Library _font_library;
};

template <typename dummy>
std::function<void (int, char const *)> context_static_members<dummy>::error_handler;

template <typename dummy>
std::function<void (GLFWwindow * /*window*/
        , int /*key*/
        , int /*scancode*/
        , int /*action*/
        , int /*modsint*/)> context_static_members<dummy>::key_handler;

template <typename dummy>
std::function<void (GLFWwindow * /*window*/
        , int /*width*/
        , int /*height*/)> context_static_members<dummy>::framebuffer_size_handler {[] (
                  GLFWwindow * /*window*/
                , int width
                , int height) {
                    // By defualt rearranges OpenGL viewport to the current
                    // framebuffer size.
                    glViewport(0, 0, width, height);
                }};

template <typename dummy>
std::function<void (GLFWmonitor * /*monitor*/
        , int /*event*/)> context_static_members<dummy>::monitor_handler;

}} // namespace pfs::griotte
