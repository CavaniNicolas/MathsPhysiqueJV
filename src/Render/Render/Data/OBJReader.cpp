
#include <iostream>
#include <fstream>
#include <sstream>

#include "Render/Data/OBJReader.hpp"

namespace render
{
namespace IO
{

render::Mesh OBJReader::readOBJFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if(!file.is_open())
    {
        throw std::runtime_error(std::string(__func__) + " : Could not load the file " + filename);
    }

    std::cout << "Reading OBJ from file : " << filename << std::endl;

    std::stringstream strstream;
    char line[256];

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    while(!file.eof())
    {
        file.getline(line, 256);
        strstream << line;
    }

    //    std::cout << strstream.str() << std::endl;

    return Mesh(vertices, indices);
}

} // namespace IO
} // namespace render
