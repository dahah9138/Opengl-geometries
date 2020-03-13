#ifndef SPHERE3_H
#define SPHERE3_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Polygon.h"


class Sphere3 : public Polygon
{
public:
	Sphere3(float R = 1.0f, glm::vec3 c = glm::vec3(0.0f), int rs = 10, bool wire = false) : _R(R) {
		_center = c;
		_useWire = wire;
		_root_size = rs;
	}
	~Sphere3() { if (_mesh != 0) { delete _mesh; _mesh = 0; } }
	void init();

private:
	int convert_ijk_to_index(int i, int j, int k); // i,j indexed at 0
	float _R;
};

#endif