
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

    // 3D vertices and UV coordinates directly read from the file
    std::vector<glm::vec3> vertex;
    std::vector<glm::vec2> vertexTexture;

    // actual structure containing the coresponding 3D vertices to its UV coordinates (and normals)
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int compt = 0;

    while(!file.eof())
    {
        // get first word of the line
        file >> line;

        // if its a comment, skip it
        if(!std::strcmp(line, "#"))
        {
            file.getline(line, 256);
        }
        // if its a vertex
        else if(!std::strcmp(line, "v"))
        {
            float x, y, z;
            file >> x >> y >> z;

            //            std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
            vertex.push_back(glm::vec3(x, y, z));
        }
        // if its a texture vertex
        else if(!std::strcmp(line, "vt"))
        {
            float u, v;
            file >> u >> v;

            //            std::cout << "u: " << u << ", v: " << v << std::endl;
            vertexTexture.push_back(glm::vec2(u, v));
        }
        // if its a normal vertex
        else if(!std::strcmp(line, "vn"))
        {
            float nx, ny, nz;
            file >> nx >> ny >> nz;

            //            std::cout << "nx: " << nx << ", ny: " << ny << ", nz: " << nz << std::endl;
            // TO DO, save it
        }
        // if its an index
        else if(!std::strcmp(line, "f"))
        {
            std::string l;
            unsigned int v[3], vt[3], vn[3];

            auto slash = std::string::npos;
            for(int i = 0; i < 3; ++i)
            {
                file >> l;

                // - 1 to every vertex because they start at 1 in the file
                v[i] = std::stoi(l) - 1;

                slash = l.find("/");
                l.erase(0, slash + 1);

                vt[i] = std::stoi(l) - 1;

                slash = l.find("/");
                l.erase(0, slash + 1);

                vn[i] = std::stoi(l) - 1;

                // fill vertices by assigning texture UV coordinates to the 3D model coordinates
                vertices.push_back(Vertex{vertex[v[i]], vertexTexture[vt[i]]});
                // fill indices
                indices.push_back(compt);
                compt++;
            }

            //            std::cout << "v[0]: " << v[0] << ", vt[0]: " << vt[0] << ", vn[0]: " << vn[0] << std::endl;
        }
    }

    return Mesh(vertices, indices);
}

} // namespace IO
} // namespace render
