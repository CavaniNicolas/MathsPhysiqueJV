#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

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
