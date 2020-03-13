#include "Polygon.h"


void Polygon::draw() {
	if (_useWire) {
		_mesh->useWireMesh();
	}
	else {
		_mesh->useSolidMesh();
	}
	_mesh->Draw();
}

void Polygon::draw(const GLSL& shader) {
	if (_useWire) {
		_mesh->useWireMesh();
	}
	else {
		_mesh->useSolidMesh();
	}
	_mesh->Draw(shader);
}