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
		_width(width), _height(height), _title(title), _camera(0), prevCursorPos((double)0), _lastFrame(0.0f), _speed(15.0f), _internalCamera(false) { init(); }
	~Window() { if (_camera != 0 && _internalCamera) { delete _camera; _camera = 0; } }
	void init();
	void processInput();
	void swap();
	void pollEvents();
	void setCamera(Camera& camera) { _camera = &camera; _camera->setWindowDims(_width, _height); }
	void makeCamera() { _camera = new Camera; _camera->setWindowDims(_width, _height); _internalCamera = true; }
	int getWidth() { return _width; }
	int getHeight() { return _height; }
	Camera* getCamera() { return _camera; }
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
	bool _internalCamera;
};

// Weird stuff happens when trying to put into class

extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif