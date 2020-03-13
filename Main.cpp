#include <iostream>
#include "Simulation.h"

// TODO (Graphics):
// - Add lighting
// - Add settings to turn off lighting
// - Make some specific shaders for different objects
// - Add textures (and settings to turn off textures)
// - Add FPS counter
// - More sophistocated menu
// - Add ability to draw and name singular lines
// - Model batching (for optimization)
// - Add quaternions to replace euler angles
// - Add instancing to the cylinder
// - Add instancing to the torus
// - Add a class to manage model matrices

// TODO (Physics):
// - Incorporate relax7 code (lines 1 - 400)
// -- Free energy function
// -- Voltage function
// -- Tensor class(make a glm container maybe?)
// -- Functional derivatives function
// -- Add file reader to read in LC data
// -- Periodic boundary conditions


// main program


int main(void) {

	Simulation sim;
	
	sim.initObjects();

	sim.loop();

	return 0;
}