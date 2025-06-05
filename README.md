# Cyber Runner

A cyberpunk themed auto side scrolling platformer/runner game made in my own C++ game engine, using the Simple and Fast Multimedia Library (SFML) for handling graphics.

## Entity Component System Architecture
![ezgif-2c588bb09d2ec3](https://github.com/user-attachments/assets/952d76d2-06e4-42d3-b585-80043157cec8)

The game is built using my custom C++ engine from the ground up, using the flexible Entity Component Systems architecture as a basic framework. Each entity in the game, including the player, tile, and background, can be assigned any component at will depending on the desired behaviour. Example of Components include Transform for storing the position and velocity, Animation for loading and playing SFML textures and sprites, and BoundingBox for describing the size of entities then computing collisions and simulating physics.

## Textures, Assets, and Animations
![ezgif-2aa862a812a5aa](https://github.com/user-attachments/assets/95f2167f-f05d-4540-bbcc-7a740a344534)

Compared to my last game Geometry Wars, Cyber Runner takes a big step visually by introducing 32-bit assets. The game engine now reads in sprites, textures, fonts, and animations from file and stores them for use at any time during the game as objects appear. Another addition is scenes, and the ability to store multiple of them and switch between scenes. We can now have a scene for the main menu and another scene for the level, then easily make a new scene for any possible addition to our game at a later date.

## Drag and Drop
![draganddrop2](https://github.com/user-attachments/assets/17a6a06a-6552-4e17-b6fd-624dfd45e06a)

In preparation for making a level editor, I've implemented the ability to drag and drop objects anywhere in the scene. Although intented for level editing purposes, being able to drag objects around can be a whole game mechanic in itself! Here, I'm showing how you can drag tiles in the game around in real time, moving obstacles out of the way and also creating footstools for the player to stand on. We can even drag the player and dangle him around like a puppet.
