//
// Created by Ethan McTague on 2019-12-10.
//

#include "Window.h"

int Window::windowCount = 0;

Window::Window(int width, int height, const char *title) {
    windowCount++;

    if (!glfwInit()) throw WindowInitFailedException("GLFW Initialization");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) throw WindowInitFailedException("Window Creation");

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) throw WindowInitFailedException("GLEW Initialization");

    glEnable(GL_DEPTH_TEST);

    previousTime = glfwGetTime();
    previousMousePos = getMousePos();
}

Window::~Window() {
    windowCount--;
    glfwDestroyWindow(window);

    if (windowCount < 1) {
        glfwTerminate();
    }
}

bool Window::isOpen() const {
    return !glfwWindowShouldClose(window);
}

WindowFrame Window::newFrame() {
    WindowFrame frame {};

    glfwPollEvents();
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    frame.time = glfwGetTime();
    frame.deltaTime = frame.time - previousTime;
    frame.mousePos = getMousePos();
    frame.mouseDelta = frame.mousePos - previousMousePos;
    previousMousePos = frame.mousePos;

    return frame;
}

glm::vec2 Window::getMousePos() const {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    return glm::vec2(mouseX, mouseY);
}

bool Window::isKeyDown(int key) const {
    return glfwGetKey(window, key);
}
