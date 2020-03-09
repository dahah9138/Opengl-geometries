#include "Rectangle.h"



// Very inefficient init

void Rectangle::init() {

	std::vector<Vertex> verts;
	std::vector<unsigned int> vecIndices;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				Vertex tempV;
				tempV.Position = _center + glm::vec3((2*i-1)*_boxHalfDims.x, (2 * j - 1) * _boxHalfDims.y, (2 * k - 1) * _boxHalfDims.z);
				tempV.Color = glm::vec3((float)(2*i + 1)/3, (float)(2*j + 1) / 3, (float)(2*k + 1) / 3);
				tempV.Normal = tempV.Position - _center; // points out from center
				tempV.Normal = glm::normalize(tempV.Normal);
				verts.push_back(tempV);
			}
		}
	}

	// Seems like I get this to have a for loop but I have no clue

	parity(0, 2, 3, vecIndices); // back
	parity(0, 4, 5, vecIndices); // left
	parity(0, 4, 6, vecIndices); // bottom
	parity(1, 5, 7, vecIndices); // top
	parity(2, 3, 7, vecIndices); // right
	parity(4, 6, 7, vecIndices); // front



	// Assign the mesh

	_mesh = new Mesh(verts, vecIndices);
}

void Rectangle::draw(const GLSL &shader) {
	if (_useWire) {
		_mesh->useWireMesh();
	}
	else {
		_mesh->useSolidMesh();
	}
	_mesh->Draw(shader);
}

void Rectangle::draw() {
	if (_useWire) {
		_mesh->useWireMesh();
	}
	else {
		_mesh->useSolidMesh();
	}
	_mesh->Draw();
}

void Rectangle::parity(int i, int j, int k, std::vector<unsigned int> &indices) {
	indices.push_back(i);
	indices.push_back(j);
	indices.push_back(k);
	indices.push_back(k);
	indices.push_back(i ^ j ^ k);
	indices.push_back(i);
}