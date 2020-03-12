#ifndef SPHERE3_H
#define SPHERE3_H

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"


class Sphere3
{
public:
	Sphere3() : _R(1.0f), _center(0.0f), _mesh(0), _useWire(true), _root_size(10) {}
	~Sphere3() { if (_mesh != 0) { delete _mesh; _mesh = 0; } }
	void init();
	void draw();

private:
	int convert_ijk_to_index(int i, int j, int k); // i,j indexed at 0
	int _root_size; // cube of this number is total vertices
	float _R;
	glm::vec3 _center;
	Mesh* _mesh;
	bool _useWire;
};

#endif