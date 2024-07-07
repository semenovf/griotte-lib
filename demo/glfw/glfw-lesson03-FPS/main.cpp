////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019-2020 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.20 Initial version
////////////////////////////////////////////////////////////////////////////////

#include "Application.hpp"
#include "fps_counter.hpp"
#include "pfs/fmt.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>

static constexpr int WINDOW_WIDTH = 400;
static constexpr int WINDOW_HEIGHT = 400;

static float angle {0.0};

using fps_counter_type = fps_counter<double>;

void initialize ()
{
    // Background color
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble left {-WINDOW_WIDTH / 2};
    GLdouble right {WINDOW_WIDTH / 2};
    GLdouble bottom {-WINDOW_HEIGHT / 2};
    GLdouble top {WINDOW_HEIGHT / 2};
    GLdouble near_val {-200.0};
    GLdouble far_val {200.0};
    glOrtho(left, right, bottom, top, near_val, far_val);

    glMatrixMode(GL_MODELVIEW);
}

void draw ()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Foreground color
    glColor3f(1.0, 1.0, 1.0);

    float scale_x = 1.0 - std::abs(std::sin(M_PI * angle / 90.0) / sqrt(3.0) / 2);
    float scale_y = scale_x;

    glPushMatrix();

    glRotatef(angle, 0.0, 0.0, 1.0);
    glScalef(scale_x, scale_y, 1.0);

    //fmt::print("scale_x = {}, scale_y = {}\n", scale_x, scale_y);

    // Cause `X Error of failed request:  GLXBadContextState ...` if no glEnd() call after
    glBegin(GL_LINES);

    for (float i = -WINDOW_WIDTH / 2.0f; i <= WINDOW_WIDTH / 2.0f; i += 20.0f) {
        glVertex2f(i, -WINDOW_HEIGHT / 2);
        glVertex2f(i, WINDOW_HEIGHT / 2);
    }

    for (float i = -WINDOW_HEIGHT / 2.0f; i <= WINDOW_HEIGHT / 2.0f; i += 20.0f) {
        glVertex2f(-WINDOW_WIDTH / 2, i);
        glVertex2f(WINDOW_WIDTH / 2, i);
    }

    glEnd();
    glPopMatrix();

    //glFlush(); // No need
}

int main ()
{
    Application app;

    return app.run( [] {
        // Create a windowed mode window and its OpenGL context
        GLFWwindow * window = glfwCreateWindow(WINDOW_WIDTH
                , WINDOW_HEIGHT
                , "Lesson 03"
                , nullptr, nullptr);

        if (!window)
            return -1;

        glfwSetWindowPos(window, 100, 200);

        fps_counter_type fpsCounter {1.0};
        fpsCounter.set_fps(30);

        Application::setKeyHandler(window, [& fpsCounter] (
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

                case GLFW_KEY_UP:
                    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                        auto fps = fpsCounter.fps();
                        fpsCounter.set_fps(++fps);
                    }
                    break;

                case GLFW_KEY_DOWN:
                    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                        auto fps = fpsCounter.fps();
                        if (fps > 0)
                            fpsCounter.set_fps(--fps);
                    }
                    break;

                default:
                    break;
            }
        });

        fmt::print("Press ESC to close window (and thus quit application) ...\n");
        fmt::print("<Arrow Up>  : increase FPS\n");
        fmt::print("<Arrow Down>: decrease FPS\n");

        // Before you can use the OpenGL API, you must have a current OpenGL
        // context. The context will remain current until you make another
        // context current or until the window owning the current context is
        // destroyed.
        // Make the window's context current.
        glfwMakeContextCurrent(window);

        // Initialize draw context
        initialize();

        unsigned int fps = fpsCounter.fps();
        bool update {fps > 0};

        auto title {fmt::format("FPS {}", fps)};
        glfwSetWindowTitle(window, title.c_str());

        while (!glfwWindowShouldClose(window)) {
            if (update) {
                fpsCounter.start(glfwGetTime());
                // Render here
                draw();

                // Swap front and back buffers
                glfwSwapBuffers(window);
                angle++;
            }

            if (fps != fpsCounter.fps()) {
                fps = fpsCounter.fps();
                title = fmt::format("FPS {}", fps);
                glfwSetWindowTitle(window, title.c_str());
            }

            // Poll for and process events
            glfwPollEvents();

            if (fps > 0) {
                if (fpsCounter.not_expired(glfwGetTime()))
                    update = false;
                else
                    update = true;
            } else {
                update = false;
            }
        }

        if (window) {
            glfwDestroyWindow(window);
            window = nullptr;
        }

        return 0;
    });
}
