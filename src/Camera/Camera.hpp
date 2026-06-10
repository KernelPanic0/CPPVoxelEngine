#pragma once
#include "../../includes/glm/glm.hpp"
#include "../../includes/glm/gtc/matrix_transform.hpp"
#include "../../includes/glm/gtc/type_ptr.hpp"
#include "../../includes/glm/glm.hpp"
#include "../../includes/glad/glad.h"

class Camera
{
private:
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

public:
    Camera(glm::vec3 cameraPos = glm::vec3(0, 0, 0));

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    const float sensitivity = 0.1f;
    float lastX = 400, lastY = 300; // Mouse pos
    float yaw = -90.0f, pitch = 0.0f;
    void MoveCamera(float xoffset, float yoffset);
    glm::mat4 GetView();
    glm::mat4 GetProjection();
};
