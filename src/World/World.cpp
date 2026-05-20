#include "World.hpp"

World::World()
{
    GenerateChunks(0, 0, 0, 0);
}

Chunk World::GetChunksForCameraPosition(double x, double z)
{
    int currentChunkX = static_cast<int>(std::floor(x / chunkSize));
    int currentChunkZ = static_cast<int>(std::floor(z / chunkSize));

    std::cout << std::ceil(x / chunkSize) << std::endl;

    // for (int dx = -renderDistance; dx < renderDistance; dx++)
    // {
    //     for (int dz = -renderDistance; dz < renderDistance; dz++)
    //     {
    //         int chunkX = currentChunkX + dx;
    //         int chunkZ = currentChunkZ + dz;

    GenerateChunks(currentChunkX, currentChunkZ, currentChunkX, currentChunkZ);
    //     }
    // }

    auto it = chunks.find({currentChunkX, currentChunkZ});
    if (it != chunks.end())
    {
        return it->second;
    }
    return Chunk(currentChunkX, currentChunkZ);
}

void World::GenerateChunks(int chunkX, int chunkZ, int chunkXC, int chunkZC)
{
    Chunk chunk(chunkX, chunkZ);

    for (int x = 0; x < chunkSize; x++)
    {
        for (int z = 0; z < chunkSize; z++)
        {
            int xOffset = x + chunkSize * chunkX;
            int zOffset = z + chunkSize * chunkZ;
            int y = yTransform(calculateNoise(xOffset, zOffset));

            // Pattern: when a neighbour is 1 below, shade the bottom corners of the side face facing it.
            //          when a neighbour is 1 above, shade the top face's edge corners closest to it.
            VertexShadingMap vertexShadingMap;
            int dy = 0;

            // +X neighbour
            dy = y - yTransform(calculateNoise(xOffset + 1, zOffset));
            if (dy == 1) // 1 below -> shade +xOffset face bottom (vertices 6, 7)
            {
                vertexShadingMap[{6, Face::PosX}] = 1;
                vertexShadingMap[{7, Face::PosX}] = 1;
            }
            else if (dy == -1) // 1 above -> shade +Y face's +xOffset edge (vertices 2, 3)
            {
                vertexShadingMap[{2, Face::PosY}] = 1;
                vertexShadingMap[{3, Face::PosY}] = 1;
            }

            // -xOffset neighbour
            dy = y - yTransform(calculateNoise(xOffset - 1, zOffset));
            if (dy == 1) // shade -xOffset face bottom (vertices 4, 5)
            {
                vertexShadingMap[{4, Face::NegX}] = 1;
                vertexShadingMap[{5, Face::NegX}] = 1;
            }
            else if (dy == -1) // shade +Y face's -xOffset edge (vertices 0, 1)
            {
                vertexShadingMap[{0, Face::PosY}] = 1;
                vertexShadingMap[{1, Face::PosY}] = 1;
            }

            // +zOffsetneighbour
            dy = y - yTransform(calculateNoise(xOffset, zOffset + 1));
            if (dy == 1) // shade +zOffsetface bottom (vertices 4, 7)
            {
                vertexShadingMap[{4, Face::PosZ}] = 1;
                vertexShadingMap[{7, Face::PosZ}] = 1;
            }
            else if (dy == -1) // shade +Y face's +zOffsetedge (vertices 0, 3)
            {
                vertexShadingMap[{0, Face::PosY}] = 1;
                vertexShadingMap[{3, Face::PosY}] = 1;
            }

            // -zOffsetneighbour
            dy = y - yTransform(calculateNoise(xOffset, zOffset - 1));
            if (dy == 1) // shade -zOffsetface bottom (vertices 5, 6)
            {
                vertexShadingMap[{5, Face::NegZ}] = 1;
                vertexShadingMap[{6, Face::NegZ}] = 1;
            }
            else if (dy == -1) // shade +Y face's -zOffsetedge (vertices 1, 2)
            {
                vertexShadingMap[{1, Face::PosY}] = 1;
                vertexShadingMap[{2, Face::PosY}] = 1;
            }

            // Diagonals: shade a single corner on the top face when the diagonal neighbour is above.

            // +X+zOffsetdiagonal -> top corner 3
            dy = y - yTransform(calculateNoise(xOffset + 1, zOffset + 1));
            if (dy == -1)
                vertexShadingMap[{3, Face::PosY}] = 1;

            // +X-zOffsetdiagonal -> top corner 2
            dy = y - yTransform(calculateNoise(xOffset + 1, zOffset - 1));
            if (dy == -1)
                vertexShadingMap[{2, Face::PosY}] = 1;

            // -X+zOffsetdiagonal -> top corner 0
            dy = y - yTransform(calculateNoise(xOffset - 1, zOffset + 1));
            if (dy == -1)
                vertexShadingMap[{0, Face::PosY}] = 1;

            // -X-zOffsetdiagonal -> top corner 1
            dy = y - yTransform(calculateNoise(xOffset - 1, zOffset - 1));
            if (dy == -1)
                vertexShadingMap[{1, Face::PosY}] = 1;

            Cube c(glm::vec3(xOffset, y, zOffset), "./assets/grass.jpg", vertexShadingMap);
            chunk.objects.push_back(c);
        }
    }

    chunks.insert({chunk.coords, chunk});
}

std::vector<Object> World::GetObjects() // thin wrapper around the objects member to make sure objects cant be modified from outside
{
    // return objects;
}