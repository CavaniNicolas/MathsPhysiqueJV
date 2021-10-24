#pragma once

#include "Render/Mesh/MeshModel.hpp"

namespace render
{
namespace mesh
{

class Pyramid //: public render::mesh::MeshModel
{
  public:
    Pyramid(const Pyramid&) = delete;
    Pyramid& operator=(const Pyramid&) = delete;

    static Pyramid& get()
    {
        // static means it will only be alocated once the first time get() is called
        static Pyramid instance;
        return instance;
    }

    static render::Mesh& getMesh()
    {
        return get().getMeshI();
    }

    static std::string getTexturePath()
    {
        return get().getTexturePathI();
    }

  private:
    Pyramid();

    // Store mesh data in vectors for the mesh
    std::vector<render::Vertex> m_verts;

    std::vector<unsigned int> m_indices;

    std::shared_ptr<render::Mesh> m_mesh;

    std::string m_texturePath;

    render::Mesh& getMeshI()
    {
        return *m_mesh;
    }

    std::string getTexturePathI()
    {
        return m_texturePath;
    }
};

} // namespace mesh
} // namespace render
