#ifndef CYLINDER_H
#define CYLINDER_H

#define _USE_MATH_DEFINES
#include <math.h>
#include "Mesh.h"

class Cylinder {
public:
	Cylinder(float R = 0.5f, float h = 3.0f, glm::vec3 center = glm::vec3(0.0f), int rs = 20, bool createCaps = true, bool wire = false) :
		_R(R), _center(center), _root_size(rs), _mesh(0), _topCap(0), _bottomCap(0), _useWire(wire), _height(h), _useCaps(createCaps) {}
	~Cylinder() {
	if (_mesh != 0) { delete _mesh; }
	if (_topCap != 0) { delete _topCap; }
	if (_bottomCap != 0) { delete _bottomCap; }
	}
	void init();
	void draw(GLSL shader);
	void useWireMesh() { _useWire = true; }
	void useSolidMesh() { _useWire = false; }

private:
	void capInit(const char* cap);
	int _root_size; // square of this number is total vertices
	float _R;
	float _height;
	glm::vec3 _center;
	Mesh* _mesh; // main body mesh
	Mesh* _topCap; // mesh for the top cap
	Mesh* _bottomCap; // mesh for the bottom cap
	bool _useWire;
	bool _useCaps; // Decide whether or not to create caps
};

#endif