#include "Rectangle.h"


void Rectangle::init() {

	geometry = "RECTANGLE3D";

	_mesh = new Mesh;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				Vertex tempV;
				tempV.Position = _center + glm::vec3((2*i-1)*_boxHalfDims.x, (2 * j - 1) * _boxHalfDims.y, (2 * k - 1) * _boxHalfDims.z);
				tempV.Color = glm::vec3((float)(2*i + 1)/3, (float)(2*j + 1) / 3, (float)(2*k + 1) / 3);
				tempV.Normal = tempV.Position - _center; // points out from center
				tempV.Normal = glm::normalize(tempV.Normal);
				_mesh->vertices.emplace_back(tempV);
			}
		}
	}

	// Seems like I get this to have a for loop but I have no clue

	for (int i = 0; i < 3; i++) {
		int powi = (int)pow(2, i);
		parity(0, (2 * i) ^ (1 + powi), 7 ^ powi);
		parity(powi, ((2 * i) ^ (1 + powi)) + powi, (7 ^ powi) + powi);
	}

	// Assign the mesh

	_mesh->setup();
}

void Rectangle::parity(int i, int j, int k) {
	_mesh->indices.emplace_back(i);
	_mesh->indices.emplace_back(j);
	_mesh->indices.emplace_back(k);
	_mesh->indices.emplace_back(k);
	_mesh->indices.emplace_back(i ^ j ^ k);
	_mesh->indices.emplace_back(i);
}