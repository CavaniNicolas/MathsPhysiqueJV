
#include <fstream>
#include <iostream>
#include <sstream>

#include "Render/Renderer.hpp"
#include "Render/Shader.hpp"

namespace render
{

Shader::Shader(const std::string& filepath): m_filepath(filepath)
{
    ShaderProgramSource source = parseShader(filepath);
    //    std::cout << "VERTEX SHADER :" << std::endl;
    //    std::cout << source.VertexSource << std::endl;
    //    std::cout << "FRAGMENT SHADER :" << std::endl;
    //    std::cout << source.FragmentSource << std::endl;
    m_rendererID = createShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_rendererID));
}

// reads the shader ressources file and returns a struct containing the Vertex
// and the Fragment Shaders
ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                // set mode to vertex
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                // set mode to fragment
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); // returns a pointer to the data in source
                                      // (source has to be alive)
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // Error handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char)); // to allocate on the stack (impossible to do:
                                                              // char message[length];)
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!"
                  << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_rendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniforms1i(const std::string& name, int value)
{
    // set the uniform value
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniforms4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    // set the uniform values
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformsMat4f(const std::string& name, const glm::mat4& matrix)
{
    // set the uniform values
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    // can replace &matrix[0][0] by glm::value_ptr(matrix) (will need #include
    // <glm/gtc/type_ptr.hpp>)
}

int Shader::getUniformLocation(const std::string& name)
{
    // look for the uniform location in the cache
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    // actually retrieve uniform location if it was not found in the cache
    GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
    if(location == -1) // just to check for errors
        std::cout << "Warning: uniform '" << name << "' doesn't exists!" << std::endl;

    // add the new uniform location to the cache
    m_uniformLocationCache[name] = location;

    return location;
}

} // namespace render
