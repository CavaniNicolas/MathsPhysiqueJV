#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.hpp"

class Camera
{
  private:
    // Stores the main vectors of the camera
    glm::vec3 m_position;
    glm::vec3 m_orientation;
    glm::vec3 m_up;

    // Prevents the camera from jumping around when first clicking left click
    bool m_firstClick;

    // Stores the width and height of the window
    int m_width;
    int m_height;

    float m_FOVdeg;

    // Adjust the speed of the camera and it's sensitivity when looking around
    float m_speed;
    float m_sensitivity;

    glm::mat4 m_view;
    glm::mat4 m_proj;

  public:
    // Camera constructor to set up initial values
    Camera(int width, int height, glm::vec3 position);

    // Updates and exports the camera matrix to the Vertex Shader
    void update(float nearPlane, float farPlane);
    // Handles camera inputs
    void handleInputs(GLFWwindow* window);

    glm::mat4 getView();
    glm::mat4 getProj();

    float getFOVdeg() const
    {
        return m_FOVdeg;
    }
    void setFOVdeg(float FOVdeg)
    {
        m_FOVdeg = FOVdeg;
    }
};
