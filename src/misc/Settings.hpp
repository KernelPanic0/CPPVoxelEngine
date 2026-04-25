#pragma once

namespace Settings
{
    inline unsigned int SCR_WIDTH = 800;
    inline unsigned int SCR_HEIGHT = 600;
    inline float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    void updateDeltaTime()
    {
        float currentFrame = glfwGetTime();
        Settings::deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
}