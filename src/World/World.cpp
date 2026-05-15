#include "World.hpp"

World::World()
{
    GenerateChunks();
}

void World::GenerateChunks()
{
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

            objects.push_back(c);
        }
    }
}

std::vector<Object> World::GetObjects() // thin wrapper around the objects member to make sure objects cant be modified from outside
{
    return objects;
}