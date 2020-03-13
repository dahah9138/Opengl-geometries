#include "GLSL.h"

GLSL::GLSL() {

}

// Compile some default shaders for basic testing

void GLSL::compileDefaultShaders() {

	// Necessary to create temp

	std::string vs = parseShaders("Shaders\\vertexShader1.vert");
	std::string fs = parseShaders("Shaders\\fragmentShader1.frag");

	if (vs.size() == 0 || fs.size() == 0) {
		return;
	}

	const char* vertexShaderSource = vs.c_str();

	const char* fragmentShaderSource = fs.c_str();

	// Create the vertex shader

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	compileErrors(vertexShader, 0);


	// Create the fragment shader

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	compileErrors(fragmentShader, 0);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	compileErrors(shaderProgram, 1);

	// No errors were found

	// Delete vertex and frag shaders

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Store the shaderProgram

	shaderObject obj(shaderProgram, "Default Shaders");

	_shader = obj;

}

// Default use chooses for shader program
void GLSL::use() {
	glUseProgram(_shader.shaderProgram);
}


// Tool for error checking at compilation

// mode:: 0 - vert and frag shader
// mode:: 1 - shaderProgram
void GLSL::compileErrors(unsigned int x_shader, unsigned int mode) {

	int success;
	char infoLog[1024];

	if (mode == 0) { // vert and frag shader
		glGetShaderiv(x_shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(x_shader, 1024, NULL, infoLog);
			std::cout << "ERROR! Shader compilation failed\n" << infoLog << std::endl;
		}
	}
	else if (mode == 1){ // shaderProgram
		glGetProgramiv(x_shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(x_shader, 1024, NULL, infoLog);
		}
	}
	else { // Undefined mode
		std::cout << "Undefined mode!" << std::endl;
	}
}


std::string GLSL::parseShaders(const char* fileName) {
	std::ifstream infile(fileName);

	if (infile.is_open()) {
	
		std::string appendedLine;
		
		std::string tempLine;

		while (std::getline(infile, tempLine)) {
			appendedLine += (tempLine + "\n");
		}
		std::cout << "Successfully parsed " << fileName << "!" << std::endl;
		infile.close();

		return appendedLine;
	}
	else {
		std::cout << "Failed to open shader file " << fileName << " while parsing!" << std::endl;
		infile.close();
		return "";
	}
}

void GLSL::setBool(const std::string& name, bool value)
{
	
	glUniform1i(glGetUniformLocation(_shader.shaderProgram, name.c_str()), (int)value);
}

void GLSL::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(_shader.shaderProgram, name.c_str()), value);
}


void GLSL::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(_shader.shaderProgram, name.c_str()), value);
}

void GLSL::customShaders(std::string vs, std::string fs) {
	std::string fvs = parseShaders(vs.c_str());
	std::string ffs = parseShaders(fs.c_str());

	if (fvs.size() == 0 || ffs.size() == 0) {
		return;
	}

	const char* vertexShaderSource = fvs.c_str();

	const char* fragmentShaderSource = ffs.c_str();

	// Create the vertex shader

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	compileErrors(vertexShader, 0);


	// Create the fragment shader

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	compileErrors(fragmentShader, 0);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	compileErrors(shaderProgram, 1);

	// No errors were found

	// Delete vertex and frag shaders

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Store the shaderProgram
	shaderObject obj(shaderProgram, "customShaderProgram");
	_shader = obj;
}


void GLSL::customShaders(std::string vs, std::string fs, std::string gs) {
	std::string fvs = parseShaders(vs.c_str());
	std::string ffs = parseShaders(fs.c_str());
	std::string fgs = parseShaders(gs.c_str());

	if (fvs.size() == 0 || ffs.size() == 0 || fgs.size() == 0) {
		return;
	}

	const char* vertexShaderSource = fvs.c_str();

	const char* fragmentShaderSource = ffs.c_str();

	const char* geometryShaderSource = fgs.c_str();

	// Create the vertex shader

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	compileErrors(vertexShader, 0);


	// Create the fragment shader

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	compileErrors(fragmentShader, 0);

	// Create the geometry shader

	unsigned int geometryShader;
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
	glCompileShader(geometryShader);

	compileErrors(geometryShader, 0);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	compileErrors(shaderProgram, 1);

	// No errors were found

	// Delete vertex and frag shaders

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Store the shaderProgram
	shaderObject obj(shaderProgram, "customShaderProgram");
	_shader = obj;
}


void GLSL::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(_shader.shaderProgram, name.c_str()), 1, &value[0]);
}
void GLSL::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(_shader.shaderProgram, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void GLSL::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(_shader.shaderProgram, name.c_str()), 1, &value[0]);
}
void GLSL::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(_shader.shaderProgram, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void GLSL::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(_shader.shaderProgram, name.c_str()), 1, &value[0]);
}
void GLSL::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(_shader.shaderProgram, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void GLSL::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(_shader.shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void GLSL::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(_shader.shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void GLSL::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(_shader.shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}