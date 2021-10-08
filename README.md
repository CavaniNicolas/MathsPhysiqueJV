# Project description

This project aims to simulate basic physics principles.
This first part is about simple particles' behaviors, and you will be able to shoot three types of particles
with their specific attributes, and see their evolution in space.


## Build Guide

Download the latest version of the project

Download the required thirdparty libraries :

- [ ] [glfw sources (3.3.4)](https://github.com/glfw/glfw)
- [ ] [glew sources (2.2.0)](https://github.com/nigels-com/glew)

Extract those libs and place them in the **thirdparty** directory of the project named as follow:
thirdparty/glew-2.2.0
thirdparty/glfw-3.3.4

Go to your build dir and compile the source using the root CMakeLists.txt

## User Guide

Once the executable is started, you will be asked many questions that you should answer in the console directly.

You will, for example, be asked to chose the projectile that you want to launch, and there you could write down
"fireball", "laser", or "bullet". You must type exactly one of these options, otherwise you will be asked to
type it again. 

Then, you will be asked to enter the position of the projectile and the shooting direction. You must follow the suggested
format exactly.

Finally, you will be asked to set the total simulation time. This represents the time during which the projectile will
be integrated and update its informations. After this time, the projecile will be destroyed and you will be asked
to launch another projectile.
