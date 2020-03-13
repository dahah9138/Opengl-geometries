#include "Simulation.h"

Simulation::~Simulation() {

	// Free the memory for the shapes

	for (int i = 0; i < _shapes.size(); i++) {
		delete _shapes[i];
	}

	_shapes.clear();
	std::vector<Polygon*>().swap(_shapes);
}


void Simulation::drawObjects() {
	glm::mat4 mvp = generateMVP();
	_programs[0].setMat4("MVP", mvp);
	_programs[0].use();
	for (int i= 0; i < _shapes.size(); i++) {
		_shapes[i]->draw();
	}
}

void Simulation::loop() {
	while (!shouldSimStop()) {
		_window.processInput();
		

		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		drawObjects();

		_window.swap();
		_window.pollEvents();
	}
	
	glfwTerminate();
}

void Simulation::initObjects() { 

	// Put desired objects in here

	const int N = 5; // Make sure to increase size for each object initialized

	_shapes.reserve(N); 

	float dt = 2 * M_PI / N;
	float t[N];

	for (int i = 0; i < N; i++) {
		t[i] = (i)*dt;
	}

	// Place the shapes in a circle

	_shapes.emplace_back(new Sphere(0.5f, glm::vec3(N * sin(t[0]), 0.0f, N * cos(t[0])), 20, true));
	_shapes.emplace_back(new Rectangle(glm::vec3(N * sin(t[1]), 0.0f, N * cos(t[1]))));
	_shapes.emplace_back(new Torus(0.5f, 0.25f, glm::vec3(N * sin(t[2]), 0.0f, N * cos(t[2])), 20, true));
	_shapes.emplace_back(new Sphere3(1.0f, glm::vec3(N*sin(t[3]), 0.0f, N*cos(t[3])), 10, true));
	_shapes.emplace_back(new Cylinder(0.5f, 3.0f, glm::vec3(N * sin(t[4]), 0.0f, N * cos(t[4])), 10, true, false));

	// Initialize all the shapes

	for (int i = 0; i < _shapes.size(); i++) {
		_shapes[i]->init();
	}

}