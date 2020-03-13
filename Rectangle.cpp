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

	for (int i = 0; i < 3; i++) {
		int powi = (int)pow(2, i);
		parity(0, (2 * i) ^ (1 + powi), 7 ^ powi, vecIndices);
		parity(powi, ((2 * i) ^ (1 + powi)) + powi, (7 ^ powi) + powi, vecIndices);
	}



	// Assign the mesh

	_mesh = new Mesh(verts, vecIndices);
}

void Rectangle::draw(GLSL shader) {
	if (_mesh == 0) { // Mesh has not been initialized.
		std::cout << "Mesh not initialized!" << std::endl;
		return;
	}
	if (_useWire) {
		_mesh->useWireMesh();
	}
	else {
		_mesh->useSolidMesh();
	}
	_mesh->Draw(shader);
}

void Rectangle::parity(int i, int j, int k, std::vector<unsigned int> &indices) {
	indices.push_back(i);
	indices.push_back(j);
	indices.push_back(k);
	indices.push_back(k);
	indices.push_back(i ^ j ^ k);
	indices.push_back(i);
}
