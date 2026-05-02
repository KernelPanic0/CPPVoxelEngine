#include "World/Scene.hpp"
#include "World/Objects/Cube.hpp"
#include "GLFW/Window.hpp"
#include "../includes/PerlinNoise.hpp"

int main()
{
    Scene scene;

    // noise
    std::random_device rd;
    const siv::PerlinNoise::seed_type seed = rd();

    const siv::PerlinNoise perlin{seed};

    for (int x = 0; x < 100; x++)
    {
        for (int z = 0; z < 100; z++)
        {
            double noise = perlin.octave2D_01(((x + 20) * 0.005), ((z + 20) * 0.005), 4);
            int yTransform = (int)-2.0f * noise * 30;

            Cube c(glm::vec3(x, yTransform, z), "./assets/grass.jpg");
            scene.AddSceneObject(c);
        }
    }

    scene.Render();
}