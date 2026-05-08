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
    Cube c1(glm::vec3(0, 0, 0), "./assets/grass.jpg");
    Cube c2(glm::vec3(0, 1, 1), "./assets/grass.jpg");

    scene.AddSceneObject(c1);
    scene.AddSceneObject(c2);

    // for (int x = 0; x < 400; x++)
    // {
    //     for (int z = 0; z < 400; z++)
    //     {
    //         double noise = perlin.octave2D_01(((x + 20) * 0.005), ((z + 20) * 0.005), 4);
    //         int yTransform = (int)-2.0f * noise * 30;

    //         Cube c(glm::vec3(x, yTransform, z), "./assets/grass.jpg");
    //         scene.AddSceneObject(c);
    //     }
    // }

    scene.Render();
}