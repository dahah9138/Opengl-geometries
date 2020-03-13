#ifndef SIMULATION_H
#define SIMULATION_H

#include "Window.h"
#include "Torus.h"
#include "Sphere.h"
#include "Sphere3.h"
#include "Rectangle.h"
#include "Cylinder.h"
#include <glm/gtc/type_ptr.hpp>

class Simulation
{
public:
	Simulation() : _window(1280, 768, "Simulation v1.0") { init(); }
	~Simulation();
	void init() { initWindow(); initShaders(); glEnable(GL_DEPTH_TEST);}
	void initWindow() {  _window.makeCamera(); }
	void initShaders() {
		GLSL shader;
		shader.customShaders("Shaders\\vertexShader1.vert", "Shaders\\fragmentShader1.frag");
		_programs.emplace_back(shader);
	}
	void initObjects();
	void drawObjects();

	glm::mat4 generateMVP() {
		glm::mat4 model(1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)_window.getWidth() / (float)_window.getHeight(), 0.1f, 1000.0f);
		glm::mat4 view = (_window.getCamera())->GetViewMatrix();

		return projection * view * model;
	}

	int shouldSimStop() { return _window.shouldWindowClose(); }
	void processInput() { _window.processInput(); }
	void swap() { _window.swap(); }
	void pollEvents() { _window.pollEvents(); }

	void loop();

private:

	// Window variables and shader programs

	Window _window;
	std::vector<GLSL> _programs;

	// Shapes

	std::vector<Polygon*> _shapes;
	
};

#endif