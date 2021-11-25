
#include <iostream>

#include "Render/DebugUtils/RenderedMeshPrinter.hpp"

namespace render
{

void RenderedMeshPrinter::debugPrintI()
{
    // Simple timer for the Particle printing
    auto currPrintTime = std::chrono::high_resolution_clock::now();
    auto duration = currPrintTime - m_prevPrintTime;
    auto durationCastS = std::chrono::duration_cast<std::chrono::seconds>(duration);

    // TODO : replace 2.0f by m_printFrequency but m_printFrequency doesnt get initialized properly in constructor :'(
    if(durationCastS.count() >= 2.0f)
    {
        std::shared_ptr<render::RenderedMesh> renderedMesh = m_renderedMesh.lock();

        if(renderedMesh != nullptr)
        {
            glm::mat4 model = renderedMesh->getModel();
            for(int i = 0; i < 4; ++i)
            {
                for(int j = 0; j < 4; ++j)
                {
                    std::cout << model[i][j] << ", ";
                }
                std::cout << std::endl;
            }

            // print vectors norm as well
            if(m_printVectorsNorm)
            {
                std::cout << "vectors norm :" << std::endl;
                for(int i = 0; i < 3; ++i)
                {
                    std::cout << model[i][0] * model[i][0] + model[i][1] * model[i][1] + model[i][2] * model[i][2]
                              << std::endl;
                }
                for(int i = 0; i < 3; ++i)
                {
                    std::cout << model[0][i] * model[0][i] + model[1][i] * model[1][i] + model[2][i] * model[2][i]
                              << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        else
        {
            std::cerr << "Debug Warning : No rigidBody were set to debug print" << std::endl;
        }
        m_prevPrintTime = currPrintTime;
    }
}

void RenderedMeshPrinter::setPrintVectorsNormI(bool shouldPrint)
{
    m_printVectorsNorm = shouldPrint;
}

void RenderedMeshPrinter::setRenderedMeshI(std::shared_ptr<RenderedMesh> renderedMesh)
{
    m_renderedMesh = renderedMesh;
}

} // namespace render
