# Project description

This project aims to simulate basic physics principles.
This first part is about simple particles' behaviors, and you will be able to shoot three types of particles
with their specific attributes, and see their evolution in space.


## Build Guide

Download the latest version of the project

Go to your build dir and compile the source using the root CMakeLists.txt

## User Guide

Once the project is compiled, you will be able to start several executables.

### Launch an object

To try to launch a rigidbody with an angular velocity, you should start mainPhase3. This will open an ImGUI window.

Here, you should set the window to be fullscreen to see everything well.

Then, just click on the button "Run simulation". You will see two cars launched in the air, and you can observe their rotations.

### Spring between two objects

Still in the mainPhase3, it is possible to also add a spring between the two cars. To do so, you can click on "Spring creation". Here there is a few settings you can change if you want, and click on "create spring". Then click on "Run simulation" to observe the behaviour of the cars.

### Collision between two cars

To test the collision between two cars, you should start mainPhase3_2. This will open an ImGUI window.
Here, you should set the window to be fullscreen to see everything well.

Then, just click on the button "Run simulation". You will see two cars launched towards each other, and you can observe their collision.


## References

Here are the links to where we inspired our code from :
- [ ] [glew and glfw sources compilation using cmake](https://github.com/opengl-tutorials/ogl/blob/master/external/CMakeLists.txt)
- [ ] [TheCherno OpenGL Youtube Tutorial](https://thecherno.com/opengl)

3D assets and Texture :
- [ ] [LowPolyCars](https://free3d.com/fr/3d-model/cartoon-vehicles-low-poly-cars-free-874937.html)
