#include "Camera.h"

void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    _Right = glm::normalize(glm::cross(_Front, _worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _Up = glm::normalize(glm::cross(_Right, _Front));
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(_Position, _Position + _Front, _Up);
}

glm::mat4 Camera::GetProjectionMatrix() {
    return glm::perspective(glm::radians(_zoom), (float)_width/(float)_height,0.1f, 100.0f);
}


void Camera::processKeyboard(Camera_Movement direction, float dt) {
    float velocity = _speed * dt;
    if (direction == FORWARD) { _Position += _Front * velocity; }
        
    if (direction == BACKWARD) { _Position -= _Front * velocity; }
       
    if (direction == LEFT) { _Position -= _Right * velocity; }
        
    if (direction == RIGHT){ _Position += _Right * velocity; }
        
}
void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= _sensitivity;
    yoffset *= _sensitivity;

    _yaw += xoffset;
    _pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    if (_zoom >= 1.0f && _zoom <= 45.0f)
        _zoom -= yoffset;
    if (_zoom <= 1.0f)
        _zoom = 1.0f;
    if (_zoom >= 45.0f)
        _zoom = 45.0f;
}