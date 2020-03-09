#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "GLSL.h"
#include "Vertex.h"
//#include "Texture.h"



class Mesh
{
public:

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh() : _vao(0), _vbo(0), _ebo(0), _instancing(false) {} // Careful with this constructor! Must call setup before use!
	Mesh(const Mesh& mesh) : _vao(mesh.getVAO()), _vbo(mesh.getVBO()), _ebo(mesh.getEBO()), _instancing(mesh.getInstancing()){
		std::cout << "Made a Mesh copy!" << std::endl;
	}
	~Mesh() { glDeleteVertexArrays(1, &_vao); glDeleteBuffers(1, &_vbo); glDeleteBuffers(1, &_ebo);}
	void Draw(const GLSL &Shader);
	void Draw(); // No textures needed to be passed
	void useWireMesh() { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
	void useSolidMesh() { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
	void useInstancing() { _instancing = true; }
	void setup() { setupMesh(); }
	void updateMesh(const int &amount, const glm::mat4 &modelMatrices) { 
		glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW); 
		glBindVertexArray(0);
	}
	void setup(const int& amount, const glm::mat4& modelMatrices) { setupMesh(amount, modelMatrices); }
	unsigned int getVAO() const { return  _vao; }
	unsigned int getVBO() const { return  _vbo; }
	unsigned int getEBO() const { return  _ebo; }
	bool getInstancing() const { return _instancing; }
	void DrawInstanced(const int& amount);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	
private:
	unsigned int _vao, _vbo, _ebo;
	bool _instancing;
	void setupMesh(const int& amount = 10, const glm::mat4& modelMatrices = glm::mat4(1.0f));
};

#endif