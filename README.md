# Project description

This project aims to simulate basic physics principles.
This first part is about simple particles' behaviors, and you will be able to shoot three types of particles
with their specific attributes, and see their evolution in space.

## Build Guide

Download the latest version of the project

Go to your build dir and compile the source using the root CMakeLists.txt

## User Guide

Once the project is compiled, you will be the executable named mainPhase4

### Selecting the parameters

Once the executable is started, you will see a window called "Parameters". Open it and expand it to see all the parameters.

Here, you will be able to choose :
- the car's linear velocity
- the car's angular velocity (rotation)
- the plan's normal
- the plan's offset

If you modify these parameters, you have to click on "Apply changes" before running the simulation to see the changes.

If you want to apply gravity to the car, you have to click on "Apply gravity" before running the simulation.

### Starting the simulation

Under the parameters section, you should see two buttons :
- Run simulation
- Pause simulation

You should click on "Run simulation" once you have all the appropriate settings. This will make the car move (except if you
did not choose a linear velocity, and did not apply the gravity force). Once the car overlaps the plan, the simulation will
automatically pause, meaning that the collision was detected.

### Notes

The only plan that is visible is the one with the normal (0, 1, 0) and the offset 0. For now, we did not have time to make
a corresponding mesh that would move and rotate according to the normal and the offset.

## References

Here are the links to where we inspired our code from :
- [ ] [glew and glfw sources compilation using cmake](https://github.com/opengl-tutorials/ogl/blob/master/external/CMakeLists.txt)
- [ ] [TheCherno OpenGL Youtube Tutorial](https://thecherno.com/opengl)

3D assets and Texture :
- [ ] [LowPolyCars](https://free3d.com/fr/3d-model/cartoon-vehicles-low-poly-cars-free-874937.html)
