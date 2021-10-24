
#include "Render/Mesh/Plan.hpp"

namespace render
{
namespace mesh
{

Plan::Plan()
{
    // Store mesh data in vectors for the mesh
    m_verts = {//              COORDINATES           /           TexCoord //
               render::Vertex{glm::vec3(-5.0f, 0.0f, 5.0f), glm::vec2(0.0f, 0.0f)},
               render::Vertex{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec2(5.0f, 0.0f)},
               render::Vertex{glm::vec3(5.0f, 0.0f, -5.0f), glm::vec2(5.0f, 5.0f)},
               render::Vertex{glm::vec3(5.0f, 0.0f, 5.0f), glm::vec2(0.0f, 5.0f)}};

    m_indices = {0, 1, 2, 2, 3, 0};

    m_mesh = std::make_shared<render::Mesh>(m_verts, m_indices);

    m_texturePath = "textures/gril_texture.png";
}

} // namespace mesh
} // namespace render
