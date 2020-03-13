#ifndef POLYGON_H
#define POLYGON_H

// Base class to use to derive all polygons used
#include "Mesh.h"

// Does not yet support instancing for all shapes
// Is not incorporated for sphere3 or torus

class Polygon
{
public:
	// Nice functions to have in inheritance
	Polygon() : _mesh(0), _center(0.0f), _useWire(false), _root_size(7) { std::cout << "Created a polygon object!" << std::endl; }
	virtual ~Polygon() { std::cout << "Freeing polygon [" << geometry << "] memory..." << std::endl; }
	virtual void draw();
	virtual void draw(const GLSL& shader);
	virtual void init(bool inst, const int& amount = 10, const glm::mat4& modelMatrices = glm::mat4(1.0f))
	{ std::cout << "ERROR::Called base init for << " << geometry << "!" << std::endl; } // Always gets overwritten in the derived polygon
	virtual void init() {} // Always gets overwritten in the derived polygon
	virtual void useWireMesh() { _useWire = true; }
	virtual void useSolidMesh() { _useWire = false; }
	virtual glm::vec3 getCenter() { return _center; }

	std::string geometry; // name of the shape

protected:
	// Reused variables
	glm::vec3 _center;
	Mesh* _mesh;
	bool _useWire;
	int _root_size;

};

#endif