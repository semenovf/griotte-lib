////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019-2020 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.18 Initial version
////////////////////////////////////////////////////////////////////////////////

#include "Application.hpp"
#include "pfs/fmt.hpp"
#include <GLFW/glfw3.h>
#include <functional>

static constexpr int WINDOW_WIDTH = 400;
static constexpr int WINDOW_HEIGHT = 400;

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
    //glTranslatef(50.0, 0.0, 0.0);  // Shift by X coordinate to right
    //glTranslatef(0.0, -50.0, 0.0); // Shift by Y coordinate to bottom
    glScalef(0.9, 0.9, 1.0);         // Change scale
    glRotatef(15.0, 0.0, 0.0, 1.0);  // Rotate about Z axis by 30 degrees
}

void draw ()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Foreground color
    glColor3f(1.0, 1.0, 1.0);

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

    glFlush(); // No need
}

int main ()
{
    Application app;

    return app.run( [] {
        // Create a windowed mode window and its OpenGL context
        GLFWwindow * window = glfwCreateWindow(WINDOW_WIDTH
                , WINDOW_HEIGHT
                , "Lesson 02"
                , nullptr, nullptr);

        if (!window)
            return -1;

        glfwSetWindowPos(window, 100, 200);

        Application::setKeyHandler(window, [] (GLFWwindow * window
                , int key
                , int /*scancode*/
                , int action
                , int /*mods*/) {

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

        // Initialize draw context
        initialize();

        while (!glfwWindowShouldClose(window)) {
            // Render here
            draw();

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
