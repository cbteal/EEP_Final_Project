# EEP_Final_Project


## Overview
This is the foundation of a random maze generator with a "smart" robot that will
navigate the randomly generated maze. At the moment there is no user interaction
and the robot navigation is very limited. In the future, adding a more robust
navigation algorithm or adding user input would be great, but time-constraints have
not allowed for adding that functionality in the immediate future.


Typical use would be to start the environment and watch the robot struggle to find
the end of the maze.


## Challenges
There were numerous challenges with this project. The most pressing challenge was
time...


Maze generation ended up eating the majority of the development time. I initially
tried to use recursion to generate a random maze, but I was getting undesired
behavior and mazes. After struggling for many hours, I decided to use an iterative
approach using a stack. Even doing that took a couple more hours.


Additionally, adding the helper functions in a meaningful way ended up taking some
iterations to fully figure out.


The robot navigation also took a considerable amount of time. I wanted to use a 
simple approach, which would imitate keeping one hand (right) on the wall at all
times. Implementing it with the physics and dynamics of the system was very
difficult. I also tried using a radar approach, but it was quickly apparent that
I would not have the time to fully implement that.


After struggling with the navigation algorithm, I finally found an approach that
worked. It uses a 45 degree angle and 90 degree angle to maintain the hold on the
right side. The speeds took some time to tune, as too fast or too slow and the
robot would miss turns or get turned around.


## Installation and Use
The project is so rudimentary at this point, that installation is as simple as
pulling the project and opening it up in docker. Then...


**make clean**


**make**


**enviro**


Then open **http://localhost** in a browser


A randomly generated maze should appear with a silly robot that will struggle
to find the end of the maze (indicated by a gold block). The robot was able to
successfully navigate the maze, but it is slow and painful to watch.


Unfortunately, I did not have more time to implement more functionality as I spent
a considerable amount of time debugging the maze generator and robot navigation. It
may have been more useful to make the robot user controlled. I may end up coming back
and adding the functionality at a later date.



