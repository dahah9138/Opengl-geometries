#ifndef GLSL_H
#define GLSL_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>


// Useful struct to store various shaders

struct shaderObject {
	shaderObject() : shaderProgram(0), shaderName(nullptr) {}
	shaderObject(unsigned int program, const char* name) : shaderProgram(program), shaderName(name) {}
	unsigned int shaderProgram;
	const char* shaderName; // Give the shader a name

	bool operator ==(const shaderObject & other) {
		if (this->shaderName == other.shaderName && this->shaderProgram == other.shaderProgram) { // Both are the same
			return true;
		}
		// Error checking
		else if (this->shaderName == other.shaderName || this->shaderProgram == other.shaderProgram) { // One is the same
			if (this->shaderName == other.shaderName) { // shader name is the same
				std::cout << "ERROR! Same shader name but different different" << std::endl;
			}
			else { // shader program has same id
				std::cout << "ERROR! Same shader program but different name" << std::endl;
			}
		} else { // Neither are the same
			
		}
		return false;
	};
};

class GLSL
{
public:
	GLSL();
	void compileDefaultShaders();
	void customShaders(std::string vs, std::string fs);
	void customShaders(std::string vs, std::string fs, std::string gs);
	void use(); // Default use

	// Setters

	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;

	unsigned int getShader() { return _shader.shaderProgram; } // Returns the shader id

private:
	// Helper function
	void compileErrors(unsigned int x_shader, unsigned int mode);
	std::string parseShaders(const char* fileName);

	shaderObject _shader; // vector of shader objects
};

#endif