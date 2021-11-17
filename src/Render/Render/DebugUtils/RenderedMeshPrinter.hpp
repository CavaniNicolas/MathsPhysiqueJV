#pragma once

#include <chrono>

#include "Render/RenderedMesh.hpp"

namespace render
{

class RenderedMeshPrinter
{
  public:
    RenderedMeshPrinter(const RenderedMeshPrinter&) = delete;
    RenderedMeshPrinter& operator=(const RenderedMeshPrinter&) = delete;

    static RenderedMeshPrinter& get()
    {
        // static means it will only be alocated once the first time get() is called
        static RenderedMeshPrinter instance;
        return instance;
    }

    static void debugPrint()
    {
        get().debugPrintI();
    }

    static void setRenderedMesh(std::shared_ptr<RenderedMesh> renderedMesh)
    {
        get().setRenderedMeshI(renderedMesh);
    }

  private:
    std::weak_ptr<RenderedMesh> m_renderedMesh;

    // time of the last particle printing
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1, 1000000000>>>
      m_prevPrintTime;

    // print particle every printFrequency seconds
    float m_printFrequency;

    void debugPrintI();
    void setRenderedMeshI(std::shared_ptr<RenderedMesh> renderedMesh);

    RenderedMeshPrinter(): m_prevPrintTime(std::chrono::high_resolution_clock::now()), m_printFrequency(2.0f) {}
};

} // namespace render
