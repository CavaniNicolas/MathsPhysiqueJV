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

### Creating a blob

Once the project is compiled, you will be able to start 2 executables : mainPhase1 or mainPhase2.

As we worked on the phase 2, you should start mainPhase2. This will open an ImGUI window.

Here, you should set the window to be fullscreen to see everything well.

Then, you will start working on the blob you want to create by selecting options in the darker window in the top left of the main window.
In this window, the first line allows you to set the camera FOV. Increase it to have a wider view, and decrease it to zoom in.
The second line, named "Blob creation" will allow you to configure everything to create a blob.
If you click on it, you will be able to change every parameter (number of particles to create the blob, springs' strength to keep the particles together...).
If you have any doubt on what the parameter will actually do, just get your mouse cursor over the '?' symbol next to an input.

Once you finished setting the parameters for your blob, you can hit the button "Create blob" to actually create the blob in the graphical interface.

But here, the blob won't be moving, and that's normal. You should then hit the button "Run simulation" to see it move.

Once the blob is created, you will also be able to access 3 sliders, which will allow you to move the blob in each cartesian axis.
This slider adds velocity to the first particle actually created. This will lead to strange movements as this particle will suffer many contacts with the
other particles, but this will allow to make your blob move wherever you want, as the other particles will also be attracted.

### Visualizing the resting contact (Particule au repos)

If you tried to create a blob with more than 1 particle, you have probably seen that the particles actually bounce on the floor forever. This is because
of the way we implemented the resting contact. In order to detect it, whenever we have a contact, we check if the y accelertion is only created by
the gravity force. If so, we check if the new y velocity (after contact) is below a certain threshold. If so, it means that the particle's bounces
aren't significant enough, and that, in the real life, the particle would have probably stopped bouncing. This is why we put the particle in a resting
state. This means that the gravity force will no longer be applied on it. Though, as soon as any other force is applied to the particle, it will leave
the resting state, and the gravity force will be applied again.

Leading to our problem : if we have many particles, multiple spring forces will be applied to each one of them, making them leave the resting state...
The drag will also take the particle out of the resting state...

So, if you want to visualize the resting contact properly, just create a single particle with no drag and after some bounces, the particle should stabilize
in the y axis. You should still be able to move it with the cursors in the x and z axis.