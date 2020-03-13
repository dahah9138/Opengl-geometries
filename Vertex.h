#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
	Vertex() : Position(0.0f), Color(0.0f), Normal(0.0f) {}
	Vertex(glm::vec3& pos, glm::vec3& color, glm::vec3& norm) : Position(pos), Color(color), Normal(norm) {}
	//Vertex(const Vertex& vert) : Position(vert.Position), Color(vert.Color), Normal(vert.Normal) { std::cout << "Make a Vertex copy!" << std::endl; }
	glm::vec3 Position;	// position of the vertex
	glm::vec3 Color;	// color of the vertex
	glm::vec3 Normal;	// normal vector
	//glm::vec2 UV;		// texture coordinates /* This is superfluous information that can be taken out to be quicker */
};

#endif