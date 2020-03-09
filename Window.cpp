#include "Window.h"


void Window::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(_width, _height, _title, NULL, NULL);

	if (_window == 0) {
		std::cout << "Failed to open window!" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);


	// Init GLAD as well

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Disables cursor and keeps centered

	//glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


// Very basic input processing function
void Window::processInput() {
	
	double xpos, ypos;

	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);

	if (_camera == 0) {
		std::cout << "Camera not initialized!" << std::endl;
		return;
	}

	// Make camera speed const

	float currentFrame = glfwGetTime();
	float dt = currentFrame - _lastFrame;
	_lastFrame = currentFrame;

	_camera->setSpeed(_speed * dt);
	


	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		_camera->processKeyboard(FORWARD, _camera->getSpeed());
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		_camera->processKeyboard(BACKWARD, _camera->getSpeed());
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		_camera->processKeyboard(LEFT, _camera->getSpeed());
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		_camera->processKeyboard(RIGHT, _camera->getSpeed());
	if (glfwGetKey(_window, GLFW_KEY_Z) == GLFW_PRESS) // NOT IMPLEMENTED YET
		_camera->ProcessMouseScroll(0.05); // zoom in
	if (glfwGetKey(_window, GLFW_KEY_X) == GLFW_PRESS) // NOT IMPLEMENTED YET
		_camera->ProcessMouseScroll(-0.05); // zoom out


	glfwGetCursorPos(_window, &xpos, &ypos);
	xpos = xpos;
	ypos = ypos;
	if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		
		_camera->processMouseMovement( -xpos+prevCursorPos.x, ypos-prevCursorPos.y);
		
	}

	prevCursorPos.x = xpos;
	prevCursorPos.y = ypos;
}

// Container for glfwSwapBuffers
void Window::swap() {
	glfwSwapBuffers(_window);
}

// Container for glfwPollEvents
void Window::pollEvents() {
	glfwPollEvents();
}

int Window::shouldWindowClose() {
	return glfwWindowShouldClose(_window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
