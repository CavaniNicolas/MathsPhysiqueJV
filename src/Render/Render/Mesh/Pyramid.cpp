
#include "Render/Mesh/Pyramid.hpp"

namespace render
{
namespace mesh
{

Pyramid::Pyramid()
{
    // Store mesh data in vectors for the mesh
    m_verts = {//              COORDINATES           /           TexCoord    //
               render::Vertex{glm::vec3(-2.0f, 0.0f, 2.0f), glm::vec2(0.32f, 0.32f)},
               render::Vertex{glm::vec3(2.0f, 0.0f, 2.0f), glm::vec2(0.69f, 0.32f)},
               render::Vertex{glm::vec3(2.0f, 0.0f, -2.0f), glm::vec2(0.69f, 0.69f)},
               render::Vertex{glm::vec3(-2.0f, 0.0f, -2.0f), glm::vec2(0.32f, 0.69f)},

               render::Vertex{glm::vec3(0.0f, 2.8f, 0.0f), glm::vec2(0.5f, 0.0f)},
               render::Vertex{glm::vec3(0.0f, 2.8f, 0.0f), glm::vec2(1.0f, 0.5f)},
               render::Vertex{glm::vec3(0.0f, 2.8f, 0.0f), glm::vec2(0.5f, 1.0f)},
               render::Vertex{glm::vec3(0.0f, 2.8f, 0.0f), glm::vec2(0.0f, 0.5f)},

               render::Vertex{glm::vec3(0.0f, -2.8f, 0.0f), glm::vec2(0.5f, 0.0f)},
               render::Vertex{glm::vec3(0.0f, -2.8f, 0.0f), glm::vec2(1.0f, 0.5f)},
               render::Vertex{glm::vec3(0.0f, -2.8f, 0.0f), glm::vec2(0.5f, 1.0f)},
               render::Vertex{glm::vec3(0.0f, -2.8f, 0.0f), glm::vec2(0.0f, 0.5f)}

    };

    m_indices = {0, 1, 2, 2, 3, 0, 0, 1, 4, 1, 2, 5, 2, 3, 6, 3, 0, 7, 0, 1, 8, 1, 2, 9, 2, 3, 10, 3, 0, 11};

    m_mesh = std::make_shared<render::Mesh>(m_verts, m_indices);

    m_texturePath = "textures/fire_texture_pyramid.png";
}

} // namespace mesh
} // namespace render
