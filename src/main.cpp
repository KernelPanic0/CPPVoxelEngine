#include "World/Scene.hpp"
#include "World/Objects/Cube.hpp"
#include "GLFW/Window.hpp"
#include "../includes/PerlinNoise.hpp"

// This logic will need to be moved into its own chunking class and the magic numbers will need to be given a name
// noise
std::random_device rd;
const siv::PerlinNoise::seed_type seed = rd();

const siv::PerlinNoise perlin{seed};
constexpr double calculateNoise(int x, int z) { return perlin.octave2D_01(((x + 20) * 0.005), ((z + 20) * 0.005), 4); }

int main()
{
    Scene scene;

    // for (int x = 0; x < 10; x++)
    // {
    //     // Check neighbours to determine each vertexes shading value

    // std::map<int, VertexShading> vertexShadingMap;
    // vertexShadingMap[5] = {Face::NegZ, 1}; // back-bottom-left corner, only on the -Z face
    // vertexShadingMap[6] = {Face::NegZ, 1}; // back-bottom-right corner, only on the -Z face

    // Cube c1(glm::vec3(0, 0, 0), "./assets/snow.png", vertexShadingMap);
    // Cube c2(glm::vec3(0, -1, -1), "./assets/grass.jpg");
    // // Cube c3(glm::vec3(0, 1, -1), "./assets/grass.jpg", vertexShadingMap);

    // scene.AddSceneObject(c1);
    // scene.AddSceneObject(c2);
    // scene.AddSceneObject(c3);
    // }

    for (int x = 0; x < 10; x++)
    {
        for (int z = 0; z < 10; z++)
        {
            double noise = calculateNoise(x, z);
            int yTransform = (int)-2.0f * noise * 30;

            // Check neighbours to determine each vertex's shading value
            std::map<int, VertexShading> vertexShadingMap;

            if (x < 10 &&                                                      // If not at edge
                yTransform - (int)(-2.0f * calculateNoise(x + 1, z) * 30) == 1 // The next X neighbour will be one block below. Shade the +X face's bottom.
            )
            {
                vertexShadingMap[6] = {Face::PosX, 1}; // back-bottom-left corner, only on the -Z face
                vertexShadingMap[7] = {Face::PosX, 1}; // back-bottom-right corner, only on the -Z face
            }

            Cube c(glm::vec3(x, yTransform, z), "./assets/snow.png", vertexShadingMap);
            scene.AddSceneObject(c);
        }
    }

    scene.Render();
}