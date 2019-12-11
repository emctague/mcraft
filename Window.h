//
// Created by Ethan McTague on 2019-12-10.
//

#ifndef MCRAFT_WINDOW_H
#define MCRAFT_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <exception>
#include <string>

/**
 * WindowFrame - Represents the state of the Window during a particular frame.
 *
 * This simple structure stores information about timing and input for the active
 * frame, such that it may be handled easily.
 */
struct WindowFrame {
    /// Seconds from window system initialization to start of frame.
    double time;

    /// Seconds from start of last frame to start of current frame.
    double deltaTime;

    /// Mouse position within window, in screen coordinates.
    glm::vec2 mousePos;

    /// Offset from mouse position in previous frame, in screen coordinates.
    glm::vec2 mouseDelta;
};


/**
 * WindowInitFailedException - Represents a failure to initialize the window.
 */
class WindowInitFailedException : public std::exception {
    std::string message;

public:

    /**
     * Initialize an exception.
     * @param initStage Representation of the stage of window creation at which a failure occurred.
     */
    explicit WindowInitFailedException(const std::string& initStage) {
        message = "Window initialization failed during: " + initStage;
    }

    [[nodiscard]] const char *what() const noexcept override
    {
        return message.c_str();
    }
};


/**
 * Window - An window for rendering OpenGL graphics.
 *
 * Based on the GLFW windowing library, the Window provides a simple abstraction to
 * GLFW concepts.
 *
 * Event handling and presentation are both handled by the newFrame method, which
 * may be called within a loop.
 */
class Window {

    /// The number of active `Window` instances - used to decide when to tear down GLFW.
    static int windowCount;

    /// The GLFW window handle for this window.
    GLFWwindow *window;

    /// The previous `time` value, for calculating delta time.
    double previousTime;

    /// The previous mouse position value, for calculating deltas.
    glm::vec2 previousMousePos{};

public:

    /**
     * Initialize a window and its context, making it visible immediately.
     *
     * This window will use OpenGL 3.3, be non-resizable, and have depth testing
     * enabled.
     *
     * @param width  The width of the window, in screen coordinates.
     * @param height The height of the window, in screen coordinates.
     * @param title  The title of the window.
     */
    Window(int width, int height, const char *title);

    /// Teardown the window, and automatically terminate GLFW if required.
    ~Window();

    /// Indicates if the window is still open / in use.
    [[nodiscard]] bool isOpen() const;

    /// Check if the given key (GLFW_KEY_<x>) is pressed.
    [[nodiscard]] bool isKeyDown(int key) const;

    /**
     * Poll for events and present the current frame, setting up a new one.
     *
     * @return The state of the new frame - timing, inputs, etc.
     */
    WindowFrame newFrame();

private:

    /// Obtain the current mouse position, in screen coordinates.
    [[nodiscard]] glm::vec2 getMousePos() const;
};


#endif //MCRAFT_WINDOW_H
