#pragma once

// Include GLEW (important to be first)
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

class Window
{
  private:
    GLFWwindow* m_window;

    int m_width;
    int m_height;
    const char* m_windowName;

  public:
    Window(int width, int height, const char* windowName);

    // Initialize the window, return true if no error occured
    bool init();
    bool isBeingClosed();

    GLFWwindow* getWindow() const
    {
        return m_window;
    }

    void terminate();
};
