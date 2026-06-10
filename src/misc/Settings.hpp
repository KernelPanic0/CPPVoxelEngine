#pragma once
#include "../../includes/PerlinNoise.hpp"

namespace Settings
{
    // noise
    inline std::random_device rd;
    inline const siv::PerlinNoise::seed_type seed = rd();
    inline const siv::PerlinNoise perlin{seed};

    constexpr double calculateNoise(double x, double z) { return perlin.octave2D_01(((x + 20) * 0.005), ((z + 20) * 0.005), 4); }
    constexpr int yTransform(double noise) { return -2.0f * noise * 30; }

    inline unsigned int SCR_WIDTH = 800;
    inline unsigned int SCR_HEIGHT = 600;
    inline float deltaTime = 0.0f;
    inline float lastFrame = 0.0f;
    inline bool uiVisible = true;

    inline void updateDeltaTime()
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
}
