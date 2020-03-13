#include "Cylinder.h"


void Cylinder::init() {

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	// Create grid for body of cylinder

	// To be more efficient should really resize vector of vertices and indices

	float dlon = 2 * M_PI / _root_size;

	float dlat = _height / 2.0f; // Only need upper and lower vertices

	for (int i = 0; i < _root_size; i++) {
		// Get the longitude coordinate for i
		float lonTemp = (i)*dlon;
		float Rcos = _R * cos(lonTemp);
		float Rsin = _R * sin(lonTemp);
		for (int j = 0; j < 2; j++) {
			// Get the latitude coordinate for j
			float latTemp = (1-2*j)*dlat; // j = 1 bottom, j = 0 top
			//phi_theta.emplace_back(lonTemp, latTemp);

			// Need to initialize the indices as well

			if (i + 1 == _root_size && j == 0) { // End of the horizontal strip
				// First triangle
				indices.push_back(2 * i);
				indices.push_back(2 * i + 1);
				indices.push_back(1);
				// Second triangle
				indices.push_back(1);
				indices.push_back(2 * i);
				indices.push_back(0);

			} else if (j == 0 && 2*i+3) { // Standard connection routine
				// First triangle
				indices.push_back(2*i);
				indices.push_back(2*i+1);
				indices.push_back(2*i+3);
				// Second triangle
				indices.push_back(2*i+3);
				indices.push_back(2*i);
				indices.push_back(2*i+2);
			}



			Vertex tempVert;
			
			tempVert.Position = _center + glm::vec3(Rcos, Rsin, latTemp);
			// Get some funky colors
			tempVert.Color = glm::vec3(0.5f, 0.5f, 0.5f);

			tempVert.Normal = glm::vec3(Rcos-_center.x, Rsin-_center.y, 0.0f);
			tempVert.Normal = glm::normalize(tempVert.Normal);
			vertices.push_back(tempVert);

		}
	}

	_mesh = new Mesh(vertices, indices); // store the vertices and indices

	if (_useCaps) {
		capInit("top");
		capInit("bottom");
	}
	
}

void Cylinder::draw(GLSL shader) {
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

	if (!_useCaps) {
		return;
	}

	if (_topCap == 0 && _useCaps) { // Mesh has not been initialized.
		std::cout << "Top mesh not initialized!" << std::endl;
		return;
	}
	if (_useWire) {
		_topCap->useWireMesh();
	}
	else {
		_topCap->useSolidMesh();
	}
	_topCap->Draw(shader);

	if (_bottomCap == 0 && _useCaps) { // Mesh has not been initialized.
		std::cout << "Mesh not initialized!" << std::endl;
		return;
	}
	if (_useWire) {
		_bottomCap->useWireMesh();
	}
	else {
		_bottomCap->useSolidMesh();
	}
	_bottomCap->Draw(shader);
}

void Cylinder::capInit(const char* cap) {
	float zPos;
	bool up;
	if (cap == "top") {
		zPos = _center.z + _height / 2;
		up = true;
	}
	else if (cap == "bottom") {
		zPos = _center.z - _height / 2;
		up = false;
	}
	else {
		std::cout << "Trying to initialize an invalid cap!" << std::endl;
		return;
	}
	
	// Create the mesh for the circle
	
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Vertex middleVertex;
	middleVertex.Position = glm::vec3(_center.x, _center.y, zPos);
	middleVertex.Color = glm::vec3(1.0f, 0.0f, 0.0f); // Make it red for now

	if (up) {
		middleVertex.Normal = glm::vec3(0.0f, 0.0f, 1.0f); // Normal points up
	}
	else {
		middleVertex.Normal = glm::vec3(0.0f, 0.0f, -1.0f); // Normal points down
		middleVertex.Color = glm::vec3(0.0, 0.0f, 1.0f);
	}
	vertices.push_back(middleVertex);

	// Initialize outer vertices

	float dtheta = 2 * M_PI / _root_size;

	for (int i = 0; i < _root_size; i++) {
		float theta = i * dtheta;

		Vertex tempVert;
		tempVert.Position = _center + glm::vec3(_R * cos(theta), _R * sin(theta), zPos);
		tempVert.Color = middleVertex.Color;
		tempVert.Normal = middleVertex.Normal;
		vertices.push_back(tempVert);

		// connect indices

		if (i + 1 == _root_size) { // Connect 0 ->_root_size-1 -> _root_size ; 0 -> _root_size -> 1
			indices.push_back(0);
			indices.push_back(_root_size-1);
			indices.push_back(_root_size);
			indices.push_back(0);
			indices.push_back(_root_size);
			indices.push_back(1);
		}
		else {
			indices.push_back(0);
			indices.push_back(i);
			indices.push_back(i + 1);
		}

	}

	if (up) {
		_topCap = new Mesh(vertices, indices);
	}
	else {
		_bottomCap = new Mesh(vertices, indices);
	}

}