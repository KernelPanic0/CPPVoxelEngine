#include "Camera.hpp"

void Camera::MoveCamera(float xoffset, float yoffset)
{
    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

glm::mat4 Camera::GetView()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::GetProjection()
{

    GLint m_viewport[4];
    glGetIntegerv(GL_VIEWPORT, m_viewport);

    return glm::perspective(glm::radians(45.0f), (float)m_viewport[2] / (float)m_viewport[3], 0.1f, 1000.0f);
}

Camera::Camera(glm::vec3 cameraPos)
{
    this->cameraPos = cameraPos;
}