#ifndef CYLINDER_H
#define CYLINDER_H

#define _USE_MATH_DEFINES
#include <math.h>
#include "Polygon.h"

class Cylinder : public Polygon {
public:
	Cylinder(float R = 0.5f, float h = 3.0f, glm::vec3 center = glm::vec3(0.0f), int rs = 20, bool createCaps = true, bool wire = false) :
		_R(R), _topCap(0), _bottomCap(0), _height(h), _useCaps(createCaps) {
		_center = center;
		_root_size = rs;
		_useWire = wire;
	
	}
	~Cylinder() {
		if (_mesh != 0) { delete _mesh; }
		if (_topCap != 0) { delete _topCap; }
		if (_bottomCap != 0) { delete _bottomCap; }
	}
	void init();
	void draw();

private:
	void capInit(const char* cap);
	float _R;
	float _height;
	Mesh* _topCap; // mesh for the top cap
	Mesh* _bottomCap; // mesh for the bottom cap
	bool _useCaps; // Decide whether or not to create caps
};

#endif