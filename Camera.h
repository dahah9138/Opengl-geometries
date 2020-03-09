#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };


class Camera
{
public:
	

	Camera(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f) :
		_Front(0.0f,0.0f,-1.0f), _speed(0.1f), _sensitivity(0.1f), _zoom(45.0f), _height(768), _width(1280){
		_Position = pos;
		_worldUp = up;
		_yaw = yaw;
		_pitch = pitch;
		updateCameraVectors();
	}

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
		_Front(glm::vec3(0.0f, 0.0f, -1.0f)), _speed(0.05f), _sensitivity(0.02f), _zoom(45.0f)
	{
		_Position = glm::vec3(posX, posY, posZ);
		_worldUp = glm::vec3(upX, upY, upZ);
		_yaw = yaw;
		_pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	void processKeyboard(Camera_Movement direction, float dt);
	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

	void setPos(glm::vec3 pos) { _Position = pos; }
	float getSpeed() { return _speed; }
	float getFov() { return _zoom; }
	void setSpeed(float speed) { _speed = speed; }
	void setWindowDims(int w, int h) { _width = w; _height = h; }
	
	glm::vec3 getDir(Camera_Movement dir) {
		if (dir == RIGHT || dir == LEFT) {return _Right;}
		if (dir == FORWARD || dir == BACKWARD) { return _Front; }
	}

private:

	// Camera values
	float _yaw;
	float _pitch;
	float _speed;
	float _sensitivity;
	float _zoom;

	int _width;
	int _height;

	glm::vec3 _Position;
	glm::vec3 _Front;
	glm::vec3 _Up;
	glm::vec3 _Right;
	glm::vec3 _worldUp;

	void updateCameraVectors();
};

#endif