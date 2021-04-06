////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019-2020 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.26 Initial version
////////////////////////////////////////////////////////////////////////////////
#include "pfs/griotte/context.hpp"
#include <string>
#include <vector>

//
// [OpenGL Programming/Modern OpenGL Tutorial Text Rendering 01](https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_01)
//
static constexpr int WINDOW_WIDTH = 800;
static constexpr int WINDOW_HEIGHT = 600;

void initialize ()
{
    // Background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//
//     GLdouble left {-WINDOW_WIDTH / 2};
//     GLdouble right {WINDOW_WIDTH / 2};
//     GLdouble bottom {-WINDOW_HEIGHT / 2};
//     GLdouble top {WINDOW_HEIGHT / 2};
//     GLdouble near_val {-200.0};
//     GLdouble far_val {200.0};
//     glOrtho(left, right, bottom, top, near_val, far_val);
//
//     glMatrixMode(GL_MODELVIEW);
}

void draw ()
{
    glClear(GL_COLOR_BUFFER_BIT);

//     // Foreground color
//     glColor3f(1.0, 1.0, 1.0);
//
// //     float scale_x = 1.0 - std::abs(std::sin(M_PI * angle / 90.0) / sqrt(3.0) / 2);
// //     float scale_y = scale_x;
// //
// //     glPushMatrix();
// //
// //     glRotatef(angle, 0.0, 0.0, 1.0);
// //     glScalef(scale_x, scale_y, 1.0);
// //
// //     //fmt::print("scale_x = {}, scale_y = {}\n", scale_x, scale_y);
// //
// //     // Cause `X Error of failed request:  GLXBadContextState ...` if no glEnd() call after
// //     glBegin(GL_LINES);
// //
// //     for (float i = -WINDOW_WIDTH / 2.0f; i <= WINDOW_WIDTH / 2.0f; i += 20.0f) {
// //         glVertex2f(i, -WINDOW_HEIGHT / 2);
// //         glVertex2f(i, WINDOW_HEIGHT / 2);
// //     }
// //
// //     for (float i = -WINDOW_HEIGHT / 2.0f; i <= WINDOW_HEIGHT / 2.0f; i += 20.0f) {
// //         glVertex2f(-WINDOW_WIDTH / 2, i);
// //         glVertex2f(WINDOW_WIDTH / 2, i);
// //     }
// //
// //     glEnd();
// //     glPopMatrix();
//
//     //glFlush(); // No need
}

int main ()
{
    pfs::griotte::context app;

    if (!app.good()) {
        fmt::print("ERROR: {}", app.errorstr());
        return -1;
    }

    return app.run( [] {
        // Create a windowed mode window and its OpenGL context
        GLFWwindow * window = glfwCreateWindow(WINDOW_WIDTH
                , WINDOW_HEIGHT
                , "Lesson 06"
                , nullptr, nullptr);

        if (!window)
            return -1;

        glfwSetWindowPos(window, 100, 200);

        pfs::griotte::context::set_key_handler(window, [] (
                  GLFWwindow * window
                , int key
                , int /*scancode*/
                , int action
                , int /*mods*/) {

            switch (key) {
                case GLFW_KEY_ESCAPE:
                    if (action == GLFW_PRESS)
                        glfwSetWindowShouldClose(window, GLFW_TRUE);
                    break;

                default:
                    break;
            }
        });

        fmt::print("Press ESC to close window (and thus quit application) ...\n");

        // Before you can use the OpenGL API, you must have a current OpenGL
        // context. The context will remain current until you make another
        // context current or until the window owning the current context is
        // destroyed.
        // Make the window's context current.
        glfwMakeContextCurrent(window);

        // Initialize draw context
        initialize();

        auto title {fmt::format("Text render")};
        glfwSetWindowTitle(window, title.c_str());

        bool update {true};

        while (!glfwWindowShouldClose(window)) {
            if (update) {
                // Render here
                draw();

                // Swap front and back buffers
                glfwSwapBuffers(window);
                update = false;
            }

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
