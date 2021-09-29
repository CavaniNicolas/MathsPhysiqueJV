
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW (important to be first)
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include imgui
#include <imgui/imgui.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <Render/IndexBuffer.hpp>
#include <Render/Renderer.hpp>
#include <Render/Shader.hpp>
#include <Render/Texture.hpp>
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
    window = glfwCreateWindow(960, 540, "Moteur Physique", NULL, NULL);
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
        float positions[] =
        {//     COORDINATES     /  TexCoord  //
            -50.0f, -50.0f, 0.0f, 0.0f, 0.0f, // 0
             50.0f, -50.0f, 0.0f, 1.0f, 0.0f, // 1
             50.0f,  50.0f, 0.0f, 1.0f, 1.0f, // 2
            -50.0f,  50.0f, 0.0f, 0.0f, 1.0f  // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // create (and bind) the vertex array object
        VertexArray va;
        // create (and bind) the vertex buffer
        VertexBuffer vb(positions, 5 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(2);
        va.addBuffer(vb, layout);

        // create (and bind) the index buffer
        IndexBuffer ib(indices, sizeof(indices)/sizeof(int));
//        std::cout << sizeof(indices)/sizeof(int) << std::endl;

//        // set minimum left and right and maximum left and right values on the screen (and z axis too)
//        // ortho projection has that objects along side the z axis will always be the same size
//        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -100.0f, 100.0f);

        // set the field of view, the aspect ratio of the screen and the closest and furthest distance of objects that will be rendered
        // perspective projection has that objects further away from the camera along side the z axis will appear smaller
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)960 / 540, 0.1f, 200.0f);

        // moving the camera to the right (actually moving everything to the left)
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, -90.0f));

        Shader shader("res/shaders/basic.shader");
        shader.bind();
        // set the uniform values
        shader.setUniforms4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);

        Texture texture("res/textures/fire_texture.jpg");
        texture.bind(); // bind parameter is 0 by default
        shader.setUniforms1i("u_Texture", 0);

        // unbounds everything
        va.unbind();
        vb.unbind();
        ib.unbind();
        shader.unbind();

        Renderer renderer;

        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";

        // Setup ImGui binding
        ImGui::CreateContext();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        glm::vec3 translation(0, 0, 0);

        float r = 0.0f;
        float increment = 0.05f;

        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
               glfwWindowShouldClose(window) == 0 )
        {
            // Render Here
            renderer.clear();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // moving the model up right
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            // model view projection matrix
            glm::mat4 mvp = proj * view * model;

            // bind the shader and set the uniform values
            shader.bind();
            shader.setUniforms4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            // give the proj matrix to the shader
            shader.setUniformsMat4f("u_MVP", mvp);

            renderer.draw(va, ib, shader);

            // Draw whats on the currently bound buffer
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // unsigned is important !

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            // Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {
                ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.
                ImGui::SliderFloat3("translation", &translation.x, -100.0f, 100.0f); // Edit translation.x using a slider from -100.0f to 100.0f
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // Rendering imgui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();

        } // Check if the ESC key was pressed or the window was closed

    }

    // Cleanup imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
