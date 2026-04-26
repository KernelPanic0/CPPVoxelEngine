#pragma once
#include "../GLFW/glfw3.h"

namespace Settings
{
    inline unsigned int SCR_WIDTH = 800;
    inline unsigned int SCR_HEIGHT = 600;
    inline float deltaTime = 0.0f;
    inline float lastFrame = 0.0f;

    inline void updateDeltaTime()
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
}