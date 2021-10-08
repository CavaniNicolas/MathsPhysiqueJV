
// Include glm
#include "Render/RenderedMesh.hpp"

#include <glm/gtc/matrix_transform.hpp>

RenderedMesh::RenderedMesh(Mesh mesh, std::string textureFilepath):
  m_va(),
  m_vb(mesh.getVertices()),
  m_ib(mesh.getIndices().data(), mesh.getIndices().size()),
  m_layout(),
  m_texture(textureFilepath),
  m_model(glm::mat4(1.0f))
{
    m_layout.push<float>(3);
    m_layout.push<float>(2);
    m_va.addBuffer(m_vb, m_layout);

    //        std::cout << sizeof(indices)/sizeof(int) << std::endl;

    m_va.bind();
    m_ib.bind();
    m_texture.bind(); // bind parameter is 0 by default

    m_va.unbind();
}

void RenderedMesh::translate(glm::vec3 translation)
{
    // translate the model
    m_model = glm::translate(glm::mat4(1.0f), translation);
}

void RenderedMesh::rotate(float rotation, glm::vec3 axis)
{
    // rotate the model
    m_model = glm::rotate(m_model, glm::radians(rotation), axis);
}

void RenderedMesh::bind() const
{
    m_va.bind();
    m_texture.bind();
}

void RenderedMesh::unbind() const
{
    m_va.unbind();
    m_texture.unbind();
}

VertexArray& RenderedMesh::getVertexArray()
{
    return m_va;
}

VertexBuffer& RenderedMesh::getVertexBuffer()
{
    return m_vb;
}

IndexBuffer& RenderedMesh::getIndexBuffer()
{
    return m_ib;
}

glm::mat4 RenderedMesh::getModel() const
{
    return m_model;
}
