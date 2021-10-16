#pragma once

#include <glm/glm.hpp>
#include <string>

#include "IndexBuffer.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class RenderedMesh
{
  private:
    VertexBuffer m_vb;
    IndexBuffer m_ib;
    VertexArray m_va;
    VertexBufferLayout m_layout;

    Texture m_texture;

    glm::vec3 m_position;
    glm::vec3 m_origin;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    glm::mat4 m_model;

  public:
    RenderedMesh(Mesh mesh,
                 std::string textureFilepath,
                 glm::vec3 origin = glm::vec3(0.f),
                 glm::vec3 position = glm::vec3(0.f),
                 glm::vec3 rotation = glm::vec3(0.f),
                 glm::vec3 scale = glm::vec3(1.f));

    void updateModelMatrix();

    void translate(glm::vec3 translation);
    void rotate(float rotation, glm::vec3 axis);
    void scale(glm::vec3 scale);

    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(glm::vec3 scale);

    void bind() const;
    void unbind() const;

    VertexArray& getVertexArray();
    VertexBuffer& getVertexBuffer();
    IndexBuffer& getIndexBuffer();

    glm::mat4 getModel() const;
};
