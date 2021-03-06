#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace render
{

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
  private:
    std::string m_filepath;
    unsigned int m_rendererID;
    // caching for uniforms
    std::unordered_map<std::string, int> m_uniformLocationCache;

  public:
    Shader(const std::string& filepath);
    ~Shader();

    // We dont want to be able to copy as we simply handle it using an int
    // for the moment, and not a memory address to the actual opengl object
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void bind() const;
    void unbind() const;

    // set uniforms
    void setUniforms1i(const std::string& name, int value);
    void setUniforms4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniformsMat4f(const std::string& name, const glm::mat4& matrix);

  private:
    ShaderProgramSource parseShader(const std::string& filepath);
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

    int getUniformLocation(const std::string& name);
};

} // namespace render
