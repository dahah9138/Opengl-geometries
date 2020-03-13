#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Polygon.h"
#include <GLFW/glfw3.h> // including for time




class Sphere : public Polygon
{
public:
	Sphere(float r = 2) : _R(r), _rotate(false), _instanced(false), _instanceAmount(0) {}
	Sphere(float r, glm::vec3 center) : _R(r), _rotate(false), _instanced(false), _instanceAmount(0) { _center = center; }
	Sphere(float r, glm::vec3 center, int root_size, bool useWire = false, bool rotate = true, bool instance = false, int amount = 10) : 
		_R(r), _rotate(rotate), _instanced(instance), _instanceAmount(amount)
	{
		_center = center; 
		if (_root_size < 3) { _root_size = 3; }
		_useWire = useWire;
		_root_size = root_size;
	}
	~Sphere() { if (_mesh != 0) { delete _mesh; _mesh = 0; } }
	void init(bool inst, const int &amount = 10, const glm::mat4& modelMatrices = glm::mat4(1.0f));
	void init();
	void draw(const GLSL &shader);
	void draw();
	void update(glm::mat4& model) { _mesh->updateMesh(_instanceAmount, model); }

	glm::mat4 computeModel() {
		glm::mat4 model(1.0f);
		// Translate to center of sphere
		
		if (_rotate) {
			model = glm::translate(model, _center); // Move to center
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); // Rotate
			model = glm::translate(model, -_center); // Move back to previous position
		}
		
		

		return model;
	}

private:

	int convert_ij_to_index(int i, int j); // i,j indexed at 0
	void createSphereMesh();
	//int _root_size; // square of this number is total vertices
	float _R;
	//glm::vec3 _center;
	//Mesh* _mesh;
	//bool _useWire;
	bool _rotate;
	bool _instanced;
	int _instanceAmount;
};

#endif