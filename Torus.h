#ifndef TORUS_H
#define TORUS_H

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>

#include "Polygon.h"

class Torus : public Polygon
{
public:
	Torus() : _R1(2.0f), _R2(1.0f) { _root_size = 20; }
	Torus(float R1, float R2, glm::vec3 center = glm::vec3(0.0f), int root_size = 50, bool useWire = false) : _R1(R1), _R2(R2)
	{
		if (R2 > R1) { _R2 = R2 - R1; /* Ensure that _R2 is smaller */ }
		_center = center;
		_root_size = root_size;
		_useWire = useWire;
	}
	~Torus() { if (_mesh != 0) { delete _mesh; _mesh = 0; } }

	void init();

private:
	int convert_ij_to_index(int i, int j); // i,j indexed at 0
	float _R1, _R2; // Make sure R1 > R2
	
};

#endif