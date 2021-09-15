
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#include <GLFW/glfw3.h>


int main()
{

    if (!glfwInit())
    {
        // Initialization failed
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
    }

    std::cout << "lala" << std::endl;
    return 0;
}
