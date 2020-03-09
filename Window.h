#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>


#include <glad/glad.h> // Include this before GLFW or errors will occur!
#include <GLFW/glfw3.h>
#include "Camera.h"

// Basic class to handle creation of glfw window

class Window
{
public:
	Window(int width, int height, const char* title) : 
		_width(width), _height(height), _title(title), _camera(0), prevCursorPos((double)0), _lastFrame(0.0f), _speed(15.0f) { init(); }
	void init();
	void processInput();
	void swap();
	void pollEvents();
	void setCamera(Camera& camera) { _camera = &camera; _camera->setWindowDims(_width, _height); }
	
	int shouldWindowClose();
	GLFWwindow* getWindow() { return _window; }
private:

	

	int _width;
	int _height;
	float _lastFrame;
	float _speed;

	glm::vec2 prevCursorPos;
	const char* _title;
	GLFWwindow* _window;
	Camera* _camera;
};

// Weird stuff happens when trying to put into class

extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif