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
constexpr int yTransform(double noise) { return -2.0f * noise * 30; }

int main()
{
    // create world, create scene by passing in world to it. Render scene with "Scene.render".
    Scene scene;

    for (int x = 0; x < 100; x++)
    {
        for (int z = 0; z < 100; z++)
        {
            int y = yTransform(calculateNoise(x, z));

            // Pattern: when a neighbour is 1 below, shade the bottom corners of the side face facing it.
            //          when a neighbour is 1 above, shade the top face's edge corners closest to it.
            VertexShadingMap vertexShadingMap;
            int dy = 0;

            // +X neighbour
            dy = y - yTransform(calculateNoise(x + 1, z));
            if (dy == 1) // 1 below -> shade +X face bottom (vertices 6, 7)
            {
                vertexShadingMap[{6, Face::PosX}] = 1;
                vertexShadingMap[{7, Face::PosX}] = 1;
            }
            else if (dy == -1) // 1 above -> shade +Y face's +X edge (vertices 2, 3)
            {
                vertexShadingMap[{2, Face::PosY}] = 1;
                vertexShadingMap[{3, Face::PosY}] = 1;
            }

            // -X neighbour
            dy = y - yTransform(calculateNoise(x - 1, z));
            if (dy == 1) // shade -X face bottom (vertices 4, 5)
            {
                vertexShadingMap[{4, Face::NegX}] = 1;
                vertexShadingMap[{5, Face::NegX}] = 1;
            }
            else if (dy == -1) // shade +Y face's -X edge (vertices 0, 1)
            {
                vertexShadingMap[{0, Face::PosY}] = 1;
                vertexShadingMap[{1, Face::PosY}] = 1;
            }

            // +Z neighbour
            dy = y - yTransform(calculateNoise(x, z + 1));
            if (dy == 1) // shade +Z face bottom (vertices 4, 7)
            {
                vertexShadingMap[{4, Face::PosZ}] = 1;
                vertexShadingMap[{7, Face::PosZ}] = 1;
            }
            else if (dy == -1) // shade +Y face's +Z edge (vertices 0, 3)
            {
                vertexShadingMap[{0, Face::PosY}] = 1;
                vertexShadingMap[{3, Face::PosY}] = 1;
            }

            // -Z neighbour
            dy = y - yTransform(calculateNoise(x, z - 1));
            if (dy == 1) // shade -Z face bottom (vertices 5, 6)
            {
                vertexShadingMap[{5, Face::NegZ}] = 1;
                vertexShadingMap[{6, Face::NegZ}] = 1;
            }
            else if (dy == -1) // shade +Y face's -Z edge (vertices 1, 2)
            {
                vertexShadingMap[{1, Face::PosY}] = 1;
                vertexShadingMap[{2, Face::PosY}] = 1;
            }

            // Diagonals: shade a single corner on the top face when the diagonal neighbour is above.

            // +X+Z diagonal -> top corner 3
            dy = y - yTransform(calculateNoise(x + 1, z + 1));
            if (dy == -1)
                vertexShadingMap[{3, Face::PosY}] = 1;

            // +X-Z diagonal -> top corner 2
            dy = y - yTransform(calculateNoise(x + 1, z - 1));
            if (dy == -1)
                vertexShadingMap[{2, Face::PosY}] = 1;

            // -X+Z diagonal -> top corner 0
            dy = y - yTransform(calculateNoise(x - 1, z + 1));
            if (dy == -1)
                vertexShadingMap[{0, Face::PosY}] = 1;

            // -X-Z diagonal -> top corner 1
            dy = y - yTransform(calculateNoise(x - 1, z - 1));
            if (dy == -1)
                vertexShadingMap[{1, Face::PosY}] = 1;

            Cube c(glm::vec3(x, y, z), "./assets/grass.jpg", vertexShadingMap);
            scene.AddSceneObject(c);
        }
    }

    scene.Render();
}