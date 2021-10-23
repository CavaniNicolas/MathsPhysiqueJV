
#include <iostream>

#include "Render/Renderer.hpp"
#include "Render/Window.hpp"

namespace render
{

Window::Window(int width, int height, const char* windowName):
  m_width(width), m_height(height), m_windowName(windowName)
{
}

bool Window::init()
{
    // Initialise GLFW
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    m_window = glfwCreateWindow(m_width, m_height, m_windowName, NULL, NULL);

    if(m_window == NULL)
    {
        fprintf(stderr,
                "Failed to open GLFW window. If you have an Intel GPU, they are "
                "not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    glfwSetWindowPos(m_window, 450, 100);

    glfwSwapInterval(1);

    // Initialize GLEW (important to be after glfwMakeContextCurrent() )
    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return false;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

    // Light grey background
    GLCall(glClearColor(0.8f, 0.8f, 0.8f, 0.0f)); // 1.0f for the last one maybe

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Enables the depth buffer (to properly render texture on 3d objects) (this
    // implies to clear GL_DEPTH_BUFFER_BIT in Renderer::clear();)
    GLCall(glEnable(GL_DEPTH_TEST));

    return true;
}

bool Window::isBeingClosed()
{
    // if escape key is pressed or red cross is clicked, return false
    return glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_window) != 0;
}

void Window::terminate()
{
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}

} // namespace render
