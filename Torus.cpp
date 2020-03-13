#include "Torus.h"



void Torus::init() {
	geometry = "TORUS";
	
	// Create grid for polar and azimuthal angles

	const int rs = _root_size * _root_size;
	const int is = _root_size * _root_size * 6;

	// Longitude defined as [0, 2pi - dang]
	// Latitude defined as [0, 2pi - dang]

	_mesh = new Mesh;
	_mesh->vertices.reserve(rs);
	_mesh->indices.reserve(is);

	float dang = 2 * M_PI / _root_size;

	for (int i = 0; i < _root_size; i++) { // size - 1 because the edges are connected
		// Get the longitude coordinate for i
		float lonTemp = (i)*dang;
		float R1R2cos = _R1 + _R2 * cos(lonTemp);
		for (int j = 0; j < _root_size; j++) {
			// Get the latitude coordinate for j
			float latTemp = (j)*dang;
			//phi_theta.emplace_back(lonTemp, latTemp);

			// Need to initialize the indices as well

			if (i + 1 == _root_size) {
				// Need to connect the top to the bottom
				if (j + 1 == _root_size) { // Reached the end of horizontal strip
					// First triangle
					_mesh->indices.emplace_back(convert_ij_to_index(i, j));
					_mesh->indices.emplace_back(j + _root_size);
					_mesh->indices.emplace_back(j + 1);
					// Second triangle
					_mesh->indices.emplace_back(j + 1);
					_mesh->indices.emplace_back(convert_ij_to_index(i, j));
					_mesh->indices.emplace_back(convert_ij_to_index(i, j) + 1 - _root_size);
				}
				else { // Standard connection routine for bottom row
					// First triangle
					_mesh->indices.emplace_back(convert_ij_to_index(i, j));
					_mesh->indices.emplace_back(j + _root_size);
					_mesh->indices.emplace_back(j + _root_size + 1);
					// Second triangle
					_mesh->indices.emplace_back(j + _root_size + 1);
					_mesh->indices.emplace_back(convert_ij_to_index(i, j));
					_mesh->indices.emplace_back(convert_ij_to_index(i, j) + 1);
				}

			}
			else if (j + 1 == _root_size) { // Reached the end of the horizontal strip: subtract _size from necessary indices
			 // First triangle
				_mesh->indices.emplace_back(convert_ij_to_index(i, j));
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + _root_size);
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + 1);
				// Second triangle
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + 1);
				_mesh->indices.emplace_back(convert_ij_to_index(i, j));
				_mesh->indices.emplace_back(convert_ij_to_index(i, j) + 1 - _root_size);

			}
			else { // Standard connection routine
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
			

			tempVert.Position = _center + glm::vec3(R1R2cos * cos(latTemp), R1R2cos * sin(latTemp), _R2 * sin(lonTemp));
			
			if ((i + 2 *j) % 2 == 0) {
				tempVert.Color = glm::vec3(1.0f, 0.0f, 0.0f);
			} else if ((i + 3* j) % 3 == 0) {
				tempVert.Color = glm::vec3(0.0f, 1.0f, 1.0f);
			} else if ((i+j) % 5 == 0) {
				tempVert.Color = glm::vec3(0.0f, 0.0f, 1.0f);
			}
			else {
				tempVert.Color = glm::vec3(0.0f, 1.0f, 0.0f);
			}

			tempVert.Normal = tempVert.Position - glm::vec3(_R1*cos(latTemp), _R1*sin(latTemp), _center.z); // I think this works
			tempVert.Normal = glm::normalize(tempVert.Normal);
			_mesh->vertices.emplace_back(tempVert);
		}
	}

	//_mesh = new Mesh(vertices, indices); // store the vertices and indices
	_mesh->setup();
}

int Torus::convert_ij_to_index(int i, int j) { // i row, j column
	return i * _root_size + j;
}