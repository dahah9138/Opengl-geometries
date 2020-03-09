#ifndef TORUS_H
#define TORUS_H

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>

#include "Mesh.h"

class Torus
{
public:
	Torus() : _R1(2.0f), _R2(1.0f), _center(0.0f), _root_size(50), _mesh(0), _useWire(false) {}
	Torus(float R1, float R2, glm::vec3 center = glm::vec3(0.0f), int root_size = 50, bool useWire = false) : _R1(R1), _R2(R2), _center(center), _root_size(root_size), _mesh(0), _useWire(useWire)
	{
		if (R1 > R2) { _R2 = R1 - R2; /* Ensure that _R2 is smaller */ }
	}
	~Torus() { if (_mesh != 0) { delete _mesh; _mesh = 0; } }

	void init();
	void draw(const GLSL &shader);
	void draw();
	void useWireMesh() { _useWire = true; }
	void useSolidMesh() { _useWire = false; }

private:
	int convert_ij_to_index(int i, int j); // i,j indexed at 0
	int _root_size; // square of this number is total vertices
	float _R1, _R2; // Make sure R1 > R2
	glm::vec3 _center;
	Mesh* _mesh;
	bool _useWire;
};

#endif