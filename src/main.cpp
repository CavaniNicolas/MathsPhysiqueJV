
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW (important to be first)
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); // returns a pointer to the data in source (source has to be alive)
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char)); // to allocate on the stack (impossible to do: char message[length];)
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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


    // Initialize GLEW (important to be after glfwMakeContextCurrent() )
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // each line here is a vertex (a vertex is a point that can contain position, texture coordinates, normals, colors ...)
    // here we have got "vertex position"
    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    // Give OpenGL the data
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    std::string vertexShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) in vec4 position;"
            "\n"
            "void main()"
            "{"
            "   gl_Position = position;\n"
            "}\n";

    std::string fragmentShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) out vec4 color;"
            "\n"
            "void main()"
            "{"
            "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);

    glUseProgram(shader);

    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 )
    {
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear( GL_COLOR_BUFFER_BIT );

        // Draw whats on the currently bound buffer
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed

    glDeleteProgram(shader);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
