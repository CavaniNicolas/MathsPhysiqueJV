#pragma once

#include <chrono>

#include "PhysicsEngine/RigidBody.hpp"

namespace engine
{

class RigidBodyPrinter
{
  public:
    RigidBodyPrinter(const RigidBodyPrinter&) = delete;
    RigidBodyPrinter& operator=(const RigidBodyPrinter&) = delete;

    static RigidBodyPrinter& get()
    {
        // static means it will only be alocated once the first time get() is called
        static RigidBodyPrinter instance;
        return instance;
    }

    static void debugPrint()
    {
        get().debugPrintI();
    }

    static void setRigidBody(std::shared_ptr<RigidBody> rb)
    {
        get().setRigidBodyI(rb);
    }

  private:
    std::shared_ptr<RigidBody> m_rb;

    // time of the last particle printing
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1, 1000000000>>>
      m_prevPrintTime;

    // print particle every printFrequency seconds
    float m_printFrequency;

    void debugPrintI();
    void setRigidBodyI(std::shared_ptr<RigidBody> rb);

    RigidBodyPrinter(): m_prevPrintTime(std::chrono::high_resolution_clock::now()), m_printFrequency(2.0f) {}
};

} // namespace engine
