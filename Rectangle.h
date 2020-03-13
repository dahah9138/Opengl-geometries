#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Polygon.h"

class Rectangle : public Polygon
{
public:
	Rectangle() : _boxHalfDims(0.5f) {}
	Rectangle(glm::vec3 center, glm::vec3 halfDims = glm::vec3(0.5f)) : _boxHalfDims(halfDims) { _center = center; }
	~Rectangle() { if (_mesh != 0) { delete _mesh; _mesh = 0; } }
	void init();
	void translate(); // Not created yet
	void rotate(); // Not created yet
	
private:
	void parity(int i, int j, int k);
	glm::vec3 _boxHalfDims;
};

#endif