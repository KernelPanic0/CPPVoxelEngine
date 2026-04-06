#pragma once
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

class Camera
{
public:
    Camera();
    Camera(glm::vec3 cameraPos);

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    const float sensitivity = 0.1f;
    float lastX = 400, lastY = 300; // Mouse pos
    float yaw, pitch = 1.0f;
    void MoveCamera(float xoffset, float yoffset);
};