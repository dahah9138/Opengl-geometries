#include "Sphere3.h"

// Currently only gives embedded spheres

void Sphere3::init() {
	geometry = "SPHERE3";

	_mesh = new Mesh;

	// The indices size is likely not correct

	const int rs = _root_size * _root_size * _root_size + 2 * _root_size;
	const int is = _root_size * _root_size * (_root_size) * 6;

	_mesh->vertices.reserve(rs);
	_mesh->indices.reserve(is);

	float dlat = 2 * M_PI / _root_size;

	float dlon = M_PI / _root_size;

	float dpsi = M_PI / _root_size;

	float psiTemp = -(float)dpsi/2.0f;
	float lonTemp = -(float)dlon/2.0f;

	for (int i = 0; i < _root_size; i++) {
		psiTemp += dpsi;
		float sinpsi = sin(psiTemp);

		for (int j = 0; j < _root_size; j++) {

			lonTemp += dlon;
			float Rsintheta = _R * sin(lonTemp);

			for (int k = 0; k < _root_size; k++) {

				float latTemp = (k)*dlat;
				Vertex tempVert;

				if (j == 0 && k + 1 == _root_size) {
					_mesh->indices.emplace_back(convert_ijk_to_index(i, 0, -1));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, 0, k));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, 0, 0));

				}
				else if (j == 0) { // Connect this layer to the final vertex
					_mesh->indices.emplace_back(convert_ijk_to_index(i, 0, -1));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, 0, k));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, 0, k+1));
				}

				if (j + 1 == _root_size && k + 1 == _root_size) {
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, k));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, _root_size - 1, _root_size));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, 0));
				}
				else if (j + 1 == _root_size) { // Connect this layer to the final vertex
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, k));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, _root_size - 1, _root_size));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, k + 1));
				}
				else if (k + 1 == _root_size) { // Reached the end of the horizontal strip: subtract _size from necessary indices
			  // First triangle
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, k));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j+1, k));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, k + 1));
					// Second triangle
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, k + 1));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, k));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j - 1, k + 1));

				}
				else { // Standard connection routine
				 // First triangle
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, k));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j+1, k));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j+1, k+1));
					// Second triangle
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j + 1, k + 1));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, k));
					_mesh->indices.emplace_back(convert_ijk_to_index(i, j, k + 1));
				}


				
				//}
					// Get some funky colors
				if ((i ^ j) % 2 == 0) {
					tempVert.Color = glm::vec3(1.0f, 0.0f, 0.0f);
				}
				else if ((i | j) % 5 == 0) {
					tempVert.Color = glm::vec3(0.0f, 1.0f, 1.0f);
				}
				else if (((i ^ j) | (i | j)) % 2 == 0) {
					tempVert.Color = glm::vec3(1.0f, 0.0f, 1.0f);
				}
				else {
					tempVert.Color = glm::vec3(1.0f, 1.0f, 0.0f);
				}

				if (j == 0 && k == 0) {
					if (i % 2 == 0) {
						tempVert.Position = _center + glm::vec3(0.0f, 0.0f, _R * sinpsi); // Only need one vertex here
					}
					else {
						tempVert.Position = _center + glm::vec3(0.0f, 0.0f, -_R * sinpsi); // Only need one vertex here
					}
					tempVert.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
					_mesh->vertices.emplace_back(tempVert);
				}
				
				tempVert.Position = _center + glm::vec3(sinpsi * Rsintheta * cos(latTemp),
					sinpsi * Rsintheta * sin(latTemp),
					sinpsi * _R * cos(lonTemp));

				tempVert.Normal = tempVert.Position - _center;
				tempVert.Normal = glm::normalize(tempVert.Normal);
				_mesh->vertices.emplace_back(tempVert);

				
				if (j == _root_size - 1 && k == _root_size - 1) {
					if (i % 2 == 0) {
						tempVert.Position = _center + glm::vec3(0.0f, 0.0f, -_R * sinpsi); // Only need one vertex here
					}
					else {
						tempVert.Position = _center + glm::vec3(0.0f, 0.0f, _R * sinpsi); // Only need one vertex here
					}
					tempVert.Normal = glm::vec3(0.0f, 0.0f, -1.0f);
					_mesh->vertices.emplace_back(tempVert);
				}
				
			}
		}
	}

	_mesh->setup();
}

int Sphere3::convert_ijk_to_index(int i, int j, int k) { // i row, j column
	return i * (_root_size*_root_size + 2) + j * _root_size + k + 1;
}