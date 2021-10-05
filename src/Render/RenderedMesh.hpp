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

    glm::mat4 m_model;

public:
    RenderedMesh(Mesh mesh, std::string textureFilepath);

    void translate(glm::vec3 translation);
    void rotate(float rotation, glm::vec3 axis);

    void bind() const;
    void unbind() const;

    VertexArray& getVertexArray();
    VertexBuffer& getVertexBuffer();
    IndexBuffer& getIndexBuffer();
};
