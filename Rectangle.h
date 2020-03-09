#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Mesh.h"

class Rectangle
{
public:
	Rectangle() : _center(0.0f), _boxHalfDims(0.5f), _mesh(0), _useWire(false) {}
	Rectangle(glm::vec3 center, glm::vec3 halfDims) : _center(center), _boxHalfDims(halfDims), _mesh(0), _useWire(false) {}
	~Rectangle() { if (_mesh != 0) { delete _mesh; _mesh = 0; } }
	void init();
	void draw(const GLSL & shader);
	void draw();
	void translate(); // Not created yet
	void rotate(); // Not created yet
	void useWireMesh() { _useWire = true; }
	void useSolidMesh() { _useWire = false; }
private:
	void parity(int i, int j, int k, std::vector<unsigned int>& indices);

	Mesh *_mesh;
	glm::vec3 _center;
	glm::vec3 _boxHalfDims;
	bool _useWire;
};

#endif