#include <iostream>
#include "Window.h"
#include "GLSL.h"
#include "Camera.h"
#include "Rectangle.h"
#include "Sphere.h"
#include "Torus.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO:
// - Add lighting
// - Add settings to turn off lighting
// - Make some specific shaders for different objects
// - Add textures (and settings to turn off textures)
// - Add FPS counter
// - More sophistocated menu
// - Add ability to name singular lines
// - Add ability to make cylinders
// - Model batching (for optimization)
// - Add quaternions to replace euler angles
// - Should really add inheritance to the geometries being drawn
// - Add instancing to the cylinder
// - Add instancing to the torus
// - Add a class to manage model matrices

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 768;


// main program


int main(void) {

	// Create the window

	 Window window(SCR_WIDTH, SCR_HEIGHT, "Computing Various Realities");
	 
	// Create the vertex shader

	GLSL shaderProgram;
	//shaderRepository.compileDefaultShaders();
	shaderProgram.customShaders("Shaders\\vertexShader3.vert", "Shaders\\fragmentShader2.frag");
	//unsigned int shaderID = shaderProgram.getShader();

	Camera camera;
	window.setCamera(camera);

	// BEGIN TO INITIALIZE DATA FOR DRAWING

	//Rectangle cube(glm::vec3(1.0f), glm::vec3(1.0,2.0,1.0));

	// Base sphere model

	// Initialized at the center

	Sphere sphere(1.0f);

	glm::mat4* spheres;
	const int n = 16;

	const int size = n*n*n;
	spheres = new glm::mat4[size];
	float radius = 1.0f;
	int count = 0;
	
	// Create the model matrices for the sphere

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {

				glm::mat4 model(1.0f);
				
				// 1. translation 
				float x = (float)i * 3;
				float y = (float)j * 3;
				float z = (float)k * 3;

				model = glm::translate(model, glm::vec3(x, y, z));

				// 4. now add to list of matrices
				spheres[count] = model;
				count++;
			}
		}
	}


	//Sphere sphere(1.0f, glm::vec3(1.0f, -1.0f, -3.0f), 20, false);


	//Torus torus(2.0f, 1.0f, glm::vec3(0.0f), 20, true);


	// Initialize objects AFTER creating the camera!

	sphere.init(size, spheres[0], true);
	//cube.init();
	//torus.init();

	// GL Settings
	
	//cube.useWireMesh();
	//sphere.useWireMesh();
	//torus.useSolidMesh();

	glEnable(GL_DEPTH_TEST);
	

	while (!window.shouldWindowClose()) {
		
		window.processInput();

		//camera.processMouseMovement(0.0001f, 0.0001f);

		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		//view = glm::rotate(view, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); // Rotate
		shaderProgram.use();
		shaderProgram.setMat4("projection", projection);
		shaderProgram.setMat4("view", view);
		
		// Code to make spheres rotate.. NOT EFFICIENT

		//count = 0;
		// Draw the spheres
		//for (int i = 0; i < n; i++) {
		//	for (int j = 0; j < n; j++) {
		//		for (int k = 0; k < n; k++) {
		//
		//			glm::mat4 model(1.0f);
		//
		//			// 1. translation 
		//			float x = (float)i * 3;
		//			float y = (float)j * 3;
		//			float z = (float)k * 3;
		//			model = glm::translate(model, glm::vec3(x, y, z));
		//			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); // Rotate

					// 4. now add to list of matrices
		//			spheres[count] = model;
		//			count++;
		//		}
		//	}
		//}
		//sphere.update(spheres[0]);


		sphere.draw();// Draw the sphere instanced sphere many times
		

		window.swap();
		window.pollEvents();
	}
	delete[] spheres;
	glfwTerminate();
	return 0;
}