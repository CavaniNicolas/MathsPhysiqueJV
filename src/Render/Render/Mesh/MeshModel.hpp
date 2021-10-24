#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Render/Mesh.hpp"
#include "Render/VertexBuffer.hpp"

// the idea was to have MeshModel a virtual class, parent of Pyramid and Plan
// methods get() getMesh() would be defined in MeshModel as they are the same
// but would obviously get the data from the child object

namespace render
{
namespace mesh
{

class MeshModel
{
  public:
    MeshModel() {}
    MeshModel(const MeshModel&) = delete;
    MeshModel& operator=(const MeshModel&) = delete;
    //    virtual ~Mesh() = 0;

    static MeshModel& get()
    {
        // static means it will only be alocated once the first time get() is called
        static MeshModel instance;
        return instance;
    }

    static render::Mesh& getMesh()
    {
        return get().getMeshI();
    }

  protected:
    // Store mesh data in vectors for the mesh
    std::vector<render::Vertex> m_verts;

    std::vector<unsigned int> m_indices;

    std::shared_ptr<render::Mesh> m_mesh;

    render::Mesh& getMeshI()
    {
        return *m_mesh;
    }
};

} // namespace mesh
} // namespace render
