
// Include glm
#include <glm/gtc/matrix_transform.hpp>

#include "Render/RenderedMesh.hpp"

namespace render
{

RenderedMesh::RenderedMesh(Mesh mesh,
                           std::string textureFilepath,
                           const glm::vec3 origin,
                           const glm::vec3 position,
                           const glm::vec3 rotation,
                           const glm::vec3 scale):
  m_va(),
  m_vb(mesh.getVertices()),
  m_ib(mesh.getIndices().data(), mesh.getIndices().size()),
  m_layout(),
  m_texture(textureFilepath),

  m_model(glm::mat4(1.0f)),

  m_origin(origin),
  m_position(position),
  m_rotation(rotation),
  m_scale(scale),

  m_needModelUpdate(false)
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

// update the model matrix using rotation, position, and scale.
// needs to be called every frame because the model matrix is what is being displayed
void RenderedMesh::updateModelMatrix()
{
    m_model = glm::mat4(1.f);
    translate(-m_origin);
    glm::mat4 translation = m_model;

    m_model = glm::mat4(1.f);
    rotate(m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    rotate(m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    rotate(m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotation = m_model;

    m_model = glm::mat4(1.f);
    scale(m_scale);
    glm::mat4 scale = m_model;

    m_model = glm::mat4(1.f);
    translate(m_position + m_origin);
    glm::mat4 t2 = m_model;
    m_model = t2 * scale * rotation * translation;
}

void RenderedMesh::translate(const glm::vec3 translation)
{
    // translate the model
    m_model = glm::translate(m_model, translation);
}

void RenderedMesh::rotate(float rotation, const glm::vec3 axis)
{
    // rotate the model
    m_model = glm::rotate(m_model, glm::radians(rotation), axis);
}

void RenderedMesh::scale(const glm::vec3 scale)
{
    // scale the model
    m_model = glm::scale(m_model, scale);
}

void RenderedMesh::setPosition(const glm::vec3 position)
{
    m_position = position;
}

void RenderedMesh::setRotation(const glm::vec3 rotation)
{
    m_rotation = rotation;
}

void RenderedMesh::addRotation(const glm::vec3 rotation)
{
    m_rotation.x = fmod(m_rotation.x + rotation.x, 360);
    m_rotation.y = fmod(m_rotation.y + rotation.y, 360);
    m_rotation.z = fmod(m_rotation.z + rotation.z, 360);
}

void RenderedMesh::setScale(const glm::vec3 scale)
{
    m_scale = scale;
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

} // namespace render
