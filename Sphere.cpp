#include "Sphere.h"


// Initialize the sphere so that it can be drawn

// Does not initialize the indices for the sphere


void Sphere::init(const int &amount, const glm::mat4 &modelMatrices, bool inst) {
	_instanced = inst;
	bool condition = false;
	const int rs = _root_size * _root_size + 1;
	const int is = _root_size * (_root_size - 1) * 6 + _root_size * 3; // (_root_size - 1) rows + (_root_size) last row

	_mesh = new Mesh;

	_mesh->vertices.reserve(rs);
	_mesh->indices.reserve(is);
	// Create grid for polar and azimuthal angles

	// To be more efficient should really resize vector of vertices and indices

	// Longitude defined as [0, pi - dlon]
	// Latitude defined as [0, 2pi - dlat]

	float dlat = 2 * M_PI / _root_size;

	float dlon = M_PI / _root_size;

	

	for (int i = 0; i < _root_size; i++) { // size - 1 because the edges are connected
		// Get the longitude coordinate for i
		float lonTemp = (i) * dlon;
		float Rsintheta = _R * sin(lonTemp);
		for (int j = 0; j < _root_size; j++) {
			// Get the latitude coordinate for j
			float latTemp = (j) * dlat;


			// Need to initialize the indices as well

			if (i + 1 == _root_size && j + 1 == _root_size) {
				_mesh->indices.emplace_back(convert_ij_to_index(i, j));
				_mesh->indices.emplace_back(convert_ij_to_index(_root_size - 1, _root_size));
				_mesh->indices.emplace_back(convert_ij_to_index(i, 0));
			} else if (i + 1 == _root_size) { // Connect this layer to the final vertex
				_mesh->indices.emplace_back(convert_ij_to_index(i, j));
				_mesh->indices.emplace_back(convert_ij_to_index(_root_size-1, _root_size));
				_mesh->indices.emplace_back(convert_ij_to_index(i, j + 1));
			} else if (j + 1 == _root_size) { // Reached the end of the horizontal strip: subtract _size from necessary indices
			 // First triangle
				_mesh->indices.emplace_back(convert_ij_to_index(i, j));
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + _root_size);
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + 1);
				// Second triangle
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + 1);
				_mesh->indices.emplace_back(convert_ij_to_index(i, j));
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + 1 - _root_size);

			} else { // Standard connection routine
				// First triangle
				_mesh->indices.emplace_back(convert_ij_to_index(i, j));
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + _root_size);
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + _root_size + 1);
				// Second triangle
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + _root_size + 1);
				_mesh->indices.emplace_back(convert_ij_to_index(i, j));
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + 1);
			}
			
			Vertex tempVert;
			
			//else {
				tempVert.Position = _center + glm::vec3(Rsintheta * cos(latTemp), Rsintheta * sin(latTemp), _R * cos(lonTemp));
			//}
				// Get some funky colors
			if ((i^j) % 2 == 0) {
				tempVert.Color = glm::vec3(1.0f, 0.0f, 0.0f);
			} else if ((i|j) % 5 == 0) {
				tempVert.Color = glm::vec3(0.0f, 1.0f, 1.0f);
			}
			else if (((i^j)|(i|j)) % 2 == 0) {
				tempVert.Color = glm::vec3(1.0f, 0.0f, 1.0f);
			}
			else {
				tempVert.Color = glm::vec3(1.0f, 1.0f, 0.0f);
			}
			
			tempVert.Normal = tempVert.Position - _center;
			tempVert.Normal = glm::normalize(tempVert.Normal);
			_mesh->vertices.emplace_back(tempVert);
			if (i == _root_size - 1 && j == _root_size - 1) {
				tempVert.Position = _center + glm::vec3(0.0f, 0.0f, -_R); // Only need one vertex here
				tempVert.Normal = glm::vec3(0.0f, 0.0f, -1.0f);
				_mesh->vertices.emplace_back(tempVert);
			}
		}
	}
	
	if (_instanced) {
		_instanceAmount = amount;
		_mesh->useInstancing();
		_mesh->setup(_instanceAmount, modelMatrices);
	}
	else {
		_mesh->setup();
	}
	
	//_mesh->vertices.clear();
	
}

int Sphere::convert_ij_to_index(int i, int j) { // i row, j column
	return i * _root_size + j;
}


void Sphere::draw(const GLSL &shader) {
	if (_useWire) {
		_mesh->useWireMesh();
	}
	else {
		_mesh->useSolidMesh();
	}
	_mesh->Draw(shader);
}

void Sphere::draw() {
	if (_instanced) {
		if (_useWire) {
			_mesh->useWireMesh();
		}
		else {
			_mesh->useSolidMesh();
		}
		
		_mesh->DrawInstanced(_instanceAmount);
	}
	else {
		if (_useWire) {
			_mesh->useWireMesh();
		}
		else {
			_mesh->useSolidMesh();
		}
		_mesh->DrawInstanced(_instanceAmount);
	}
}