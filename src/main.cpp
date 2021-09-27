
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW (important to be first)
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <Render/IndexBuffer.hpp>
#include <Render/Renderer.hpp>
#include <Render/Shader.hpp>
#include <Render/VertexArray.hpp>
#include <Render/VertexBuffer.hpp>


int main()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    GLFWwindow* window;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1024, 768, "Moteur Physique", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetWindowPos(window, 450, 100);

    glfwSwapInterval(1);

    // Initialize GLEW (important to be after glfwMakeContextCurrent() )
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    GLCall(glClearColor(0.0f, 0.0f, 0.4f, 0.0f));

    {

        // each line here is a vertex (a vertex is a point that can contain position, texture coordinates, normals, colors ...)
        // here we have got "vertex position"
        float positions[] = {
            -0.5f, -0.5f, // 0
             0.5f, -0.5f, // 1
             0.5f,  0.5f, // 2
            -0.5f,  0.5f  // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        // create (and bind) the vertex array object
        VertexArray va;
        // create (and bind) the vertex buffer
        VertexBuffer vb(positions, 6 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.push<float>(2);
        va.addBuffer(vb, layout);

        // create (and bind) the index buffer
        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/basic.shader");
        shader.bind();
        // set the uniform values
        shader.setUniforms4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);

        // unbounds everything
        va.unbind();
        vb.unbind();
        ib.unbind();
        shader.unbind();

        float r = 0.0f;
        float increment = 0.05f;

        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
               glfwWindowShouldClose(window) == 0 )
        {
            // Render Here
            GLCall(glClear( GL_COLOR_BUFFER_BIT ));

            // bind the shader and set the uniform values
            shader.bind();
            shader.setUniforms4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            // bind the vertex array (same as binding the buffer and seting up its layout)
            va.bind();
            // bind the index buffer
            ib.bind();

            // Draw whats on the currently bound buffer
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // unsigned is important !

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            // Swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();

        } // Check if the ESC key was pressed or the window was closed

    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
