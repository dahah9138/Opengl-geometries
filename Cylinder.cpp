#include "Cylinder.h"


void Cylinder::init() {

	geometry = "CYLINDER";

	_mesh = new Mesh;

	std::vector<Vertex>().swap(_mesh->vertices);
	std::vector<unsigned int>().swap(_mesh->indices);

	int rs = _root_size * 2;
	int is = _root_size * 6;

	_mesh->vertices.reserve(rs);
	_mesh->indices.reserve(is);
	// Create grid for body of cylinder

	float dlon = 2 * M_PI / _root_size;

	float dlat = _height / 2.0f; // Only need upper and lower vertices

	for (int i = 0; i < _root_size; i++) {
		// Get the longitude coordinate for i
		float lonTemp = (i)*dlon;
		float Rcos = _R * cos(lonTemp);
		float Rsin = _R * sin(lonTemp);
		for (int j = 0; j < 2; j++) {
			// Get the latitude coordinate for j
			float latTemp = (1 - 2 * j) * dlat; // j = 1 bottom, j = 0 top
			//phi_theta.emplace_back(lonTemp, latTemp);

			// Need to initialize the indices as well

			if (i + 1 == _root_size && j == 0) { // End of the horizontal strip
				// First triangle
				_mesh->indices.emplace_back(2 * i);
				_mesh->indices.emplace_back(2 * i + 1);
				_mesh->indices.emplace_back(1);
				// Second triangle
				_mesh->indices.emplace_back(1);
				_mesh->indices.emplace_back(2 * i);
				_mesh->indices.emplace_back(0);

			}
			else if (j == 0 && 2 * i + 3) { // Standard connection routine
			 // First triangle
				_mesh->indices.emplace_back(2 * i);
				_mesh->indices.emplace_back(2 * i + 1);
				_mesh->indices.emplace_back(2 * i + 3);
				// Second triangle
				_mesh->indices.emplace_back(2 * i + 3);
				_mesh->indices.emplace_back(2 * i);
				_mesh->indices.emplace_back(2 * i + 2);
			}



			Vertex tempVert;

			tempVert.Position = _center + glm::vec3(Rcos, Rsin, latTemp);

			// Get a nice gray color

			tempVert.Color = glm::vec3(0.5f, 0.5f, 0.5f);

			tempVert.Normal = glm::vec3(Rcos - _center.x, Rsin - _center.y, 0.0f);
			tempVert.Normal = glm::normalize(tempVert.Normal);

			_mesh->vertices.emplace_back(tempVert);
		}
	}

	if (_useCaps) {
		capInit("top");
		capInit("bottom");
	}

	_mesh->setup(); // Let the mesh handle the rest
}

void Cylinder::draw() {
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
	_mesh->Draw();

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
	_topCap->Draw();

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
	_bottomCap->Draw();
}

void Cylinder::capInit(const char* cap) {
	float zPos;
	bool up;
	if (cap == "top") {
		int rs = _root_size + 1;
		int is = 3 * (_root_size + 1);

		_topCap = new Mesh;

		std::vector<Vertex>().swap(_topCap->vertices);
		std::vector<unsigned int>().swap(_topCap->indices);
		_topCap->vertices.reserve(rs);
		_topCap->indices.reserve(is);

		zPos = _center.z + _height / 2;
		up = true;
	}
	else if (cap == "bottom") {
		int rs = _root_size + 1;
		int is = 3 * (_root_size + 1);

		_bottomCap = new Mesh;

		std::vector<Vertex>().swap(_bottomCap->vertices);
		std::vector<unsigned int>().swap(_bottomCap->indices);
		_bottomCap->vertices.reserve(rs);
		_bottomCap->indices.reserve(is);

		zPos = _center.z - _height / 2;
		up = false;
	}
	else {
		std::cout << "Trying to initialize an invalid cap!" << std::endl;
		return;
	}

	// Create the mesh for the circle


	Vertex middleVertex;
	middleVertex.Position = glm::vec3(_center.x, _center.y, zPos);
	middleVertex.Color = glm::vec3(1.0f, 0.0f, 0.0f); // Make it red for now

	if (up) {
		middleVertex.Normal = glm::vec3(0.0f, 0.0f, 1.0f); // Normal points up
		_topCap->vertices.emplace_back(middleVertex);
	}
	else {
		middleVertex.Normal = glm::vec3(0.0f, 0.0f, -1.0f); // Normal points down
		middleVertex.Color = glm::vec3(0.0, 0.0f, 1.0f);
		_bottomCap->vertices.emplace_back(middleVertex);
	}
	

	// Initialize outer vertices

	float dtheta = 2 * M_PI / _root_size;

	for (int i = 0; i < _root_size; i++) {
		float theta = i * dtheta;

		// connect indices

		if (up) { // Init the top cap indices and vertices

			Vertex tempVert;
			tempVert.Position = _center + glm::vec3(_R * cos(theta), _R * sin(theta), (float)_height/2.0f);
			tempVert.Color = middleVertex.Color;
			tempVert.Normal = middleVertex.Normal;
			_topCap->vertices.emplace_back(tempVert);


			if (i + 1 == _root_size) { // Connect 0 ->_root_size-1 -> _root_size ; 0 -> _root_size -> 1
				_topCap->indices.emplace_back(0);
				_topCap->indices.emplace_back(_root_size - 1);
				_topCap->indices.emplace_back(_root_size);
				_topCap->indices.emplace_back(0);
				_topCap->indices.emplace_back(_root_size);
				_topCap->indices.emplace_back(1);
			}
			else {
				_topCap->indices.emplace_back(0);
				_topCap->indices.emplace_back(i);
				_topCap->indices.emplace_back(i + 1);
			}
		}
		else { // Init the bottom cap indices and vertices

			Vertex tempVert;
			tempVert.Position = _center + glm::vec3(_R * cos(theta), _R * sin(theta), -(float)_height / 2.0f);
			tempVert.Color = middleVertex.Color;
			tempVert.Normal = middleVertex.Normal;
			_bottomCap->vertices.emplace_back(tempVert);

			if (i + 1 == _root_size) { // Connect 0 ->_root_size-1 -> _root_size ; 0 -> _root_size -> 1
				_bottomCap->indices.emplace_back(0);
				_bottomCap->indices.emplace_back(_root_size - 1);
				_bottomCap->indices.emplace_back(_root_size);
				_bottomCap->indices.emplace_back(0);
				_bottomCap->indices.emplace_back(_root_size);
				_bottomCap->indices.emplace_back(1);
			}
			else {
				_bottomCap->indices.emplace_back(0);
				_bottomCap->indices.emplace_back(i);
				_bottomCap->indices.emplace_back(i + 1);
			}
		}

	}

	if (up) {
		_topCap->setup();
	}
	else {
		_bottomCap->setup();
	}

}