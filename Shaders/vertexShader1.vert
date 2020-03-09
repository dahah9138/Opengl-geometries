#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;


uniform mat4 MVP;

out vec3 ourColor;
//out vec4 vertexColor;
//out vec2 TexCoord;

void main(){
	gl_Position = MVP * vec4(aPos, 1.0f);
	//vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);
	ourColor = aColor;
	//TexCoord = UV;
}