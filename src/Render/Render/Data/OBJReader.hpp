#pragma once

#include <string>

#include "Render/Mesh.hpp"

namespace render
{
namespace IO
{

class OBJReader
{
  public:
    OBJReader() {}

    // read OBJ file and returns a Mesh
    render::Mesh readOBJFromFile(const std::string& filename);
};

} // namespace IO
} // namespace render
