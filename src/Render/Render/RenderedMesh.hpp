#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Render/IndexBuffer.hpp"
#include "Render/Mesh.hpp"
#include "Render/Texture.hpp"
#include "Render/VertexArray.hpp"
#include "Render/VertexBuffer.hpp"
#include "Render/VertexBufferLayout.hpp"

namespace render
{

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

    bool m_needModelUpdate;

  public:
    RenderedMesh(Mesh mesh,
                 std::string textureFilepath,
                 const glm::vec3 origin = glm::vec3(0.f),
                 const glm::vec3 position = glm::vec3(0.f),
                 const glm::vec3 rotation = glm::vec3(0.f),
                 const glm::vec3 scale = glm::vec3(1.f));

    void updateModelMatrix();

    void translate(const glm::vec3 translation);
    void rotate(float rotation, const glm::vec3 axis);
    void scale(const glm::vec3 scale);

    void setPosition(const glm::vec3 position);
    void setRotation(const glm::vec3 rotation);
    void addRotation(const glm::vec3 rotation);
    void setScale(const glm::vec3 scale);

    void bind() const;
    void unbind() const;

    VertexArray& getVertexArray();
    VertexBuffer& getVertexBuffer();
    IndexBuffer& getIndexBuffer();

    glm::mat4 getModel() const;

    bool getNeedModelUpdate() const
    {
        return m_needModelUpdate;
    }
    void setNeedModelUpdate(bool val)
    {
        m_needModelUpdate = val;
    }
    void setModelMatrix(glm::mat4 matrix)
    {
        m_model = matrix;
    }
};

} // namespace render
