#include "Game/Game.hpp"
#include "Game/Input.hpp"
#include "Support/DtClock.hpp"
#include "Support/Gl.hpp"

#include <cstdlib>
#include <iostream>

using namespace Y65535;

namespace {
    GLFWwindow* window;
    int width, height;
    float oldCursorX, oldCursorY;

    void DebugCallback(GLenum, GLenum, GLuint, GLenum severity, GLsizei,
                       GLchar const* message, void const*) {
        std::cout << __FUNCTION__ << ": " << message << '\n';
        if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
            std::exit(1);
        }
    }

    void InitializeGlobals() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        window = glfwCreateWindow(640, 480, "Y65535", nullptr, nullptr);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
        glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwMakeContextCurrent(window);

        glewInit();

        glDebugMessageCallback(DebugCallback, nullptr);

        glEnable(GL_DEPTH_TEST);
    }

    bool ShouldContinue() {
        return !glfwWindowShouldClose(window);
    }

    void BeforeDraw() {
        glfwSwapBuffers(window);
        glfwPollEvents();

        glfwGetWindowSize(window, &width, &height);

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Input GetInput() {
        auto strafeUp    = glfwGetKey(window, GLFW_KEY_W)     == GLFW_PRESS;
        auto strafeDown  = glfwGetKey(window, GLFW_KEY_S)     == GLFW_PRESS;
        auto strafeLeft  = glfwGetKey(window, GLFW_KEY_A)     == GLFW_PRESS;
        auto strafeRight = glfwGetKey(window, GLFW_KEY_D)     == GLFW_PRESS;

        double cursorX, cursorY;
        glfwGetCursorPos(window, &cursorX, &cursorY);
        float lookDx = cursorX - oldCursorX;
        float lookDy = cursorY - oldCursorY;
        oldCursorX = cursorX;
        oldCursorY = cursorY;

        auto shoot = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

        return Input{strafeUp, strafeDown, strafeLeft, strafeRight,
                     lookDx, lookDy,
                     shoot};
    }
}

int main() {
    InitializeGlobals();
    Game game;
    DtClock dtClock;
    for (unsigned long long i = 0; ShouldContinue(); ++i) {
        BeforeDraw();
        auto dt = dtClock.dt();
        auto input = GetInput();

        // Calibrate input before using it. This is an ugly hack and we should
        // do it properly instead.
        if (i > 6) {
            game.Step(dt, input);
        }

        game.Draw(width, height);
    }
    return 0;
}
