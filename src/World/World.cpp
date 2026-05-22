#include "World.hpp"

World::World()
{
    GenerateChunk(0, 0);
}

std::vector<Object> World::GetChunkObjectsForCameraPosition(double x, double z)
{
    int currentChunkX = static_cast<int>(std::floor(x / chunkSize));
    int currentChunkZ = static_cast<int>(std::floor(z / chunkSize));
    std::vector<Object> objects;

    for (int dx = -renderDistance; dx < renderDistance; dx++)
    {
        for (int dz = -renderDistance; dz < renderDistance; dz++)
        {
            int chunkX = currentChunkX + dx;
            int chunkZ = currentChunkZ + dz;

            GenerateChunk(chunkX, chunkZ);

            auto it = chunks.find({chunkX, chunkZ});
            if (it != chunks.end())
            {
                for (Object obj : it->second.objects)
                {
                    objects.push_back(obj);
                }
            }
            else
            {
                for (Object obj : Chunk(chunkX, chunkZ).objects)
                {
                    objects.push_back(obj);
                }
            }
        }
    }

    return objects;
}

void World::ApplyShadingMap(VertexShadingMap &sm, int blockX, int blockY, int blockZ)
{
    // Pattern: when a neighbour is 1 below, shade the bottom corners of the side face facing it.
    //          when a neighbour is 1 above, shade the top face's edge corners closest to it.
    int dy = 0;

    // +X neighbour
    dy = blockY - yTransform(calculateNoise(blockX + 1, blockZ));
    if (dy == 1) // 1 below -> shade +blockX face bottom (vertices 6, 7)
    {
        sm[{6, Face::PosX}] = 1;
        sm[{7, Face::PosX}] = 1;
    }
    else if (dy == -1) // 1 above -> shade +Y face's +blockX edge (vertices 2, 3)
    {
        sm[{2, Face::PosY}] = 1;
        sm[{3, Face::PosY}] = 1;
    }

    // -blockX neighbour
    dy = blockY - yTransform(calculateNoise(blockX - 1, blockZ));
    if (dy == 1) // shade -blockX face bottom (vertices 4, 5)
    {
        sm[{4, Face::NegX}] = 1;
        sm[{5, Face::NegX}] = 1;
    }
    else if (dy == -1) // shade +Y face's -blockX edge (vertices 0, 1)
    {
        sm[{0, Face::PosY}] = 1;
        sm[{1, Face::PosY}] = 1;
    }

    // +blockZneighbour
    dy = blockY - yTransform(calculateNoise(blockX, blockZ + 1));
    if (dy == 1) // shade +blockZface bottom (vertices 4, 7)
    {
        sm[{4, Face::PosZ}] = 1;
        sm[{7, Face::PosZ}] = 1;
    }
    else if (dy == -1) // shade +Y face's +blockZedge (vertices 0, 3)
    {
        sm[{0, Face::PosY}] = 1;
        sm[{3, Face::PosY}] = 1;
    }

    // -blockZneighbour
    dy = blockY - yTransform(calculateNoise(blockX, blockZ - 1));
    if (dy == 1) // shade -blockZface bottom (vertices 5, 6)
    {
        sm[{5, Face::NegZ}] = 1;
        sm[{6, Face::NegZ}] = 1;
    }
    else if (dy == -1) // shade +Y face's -blockZedge (vertices 1, 2)
    {
        sm[{1, Face::PosY}] = 1;
        sm[{2, Face::PosY}] = 1;
    }

    // Diagonals: shade a single corner on the top face when the diagonal neighbour is above.

    // +X+blockZdiagonal -> top corner 3
    dy = blockY - yTransform(calculateNoise(blockX + 1, blockZ + 1));
    if (dy == -1)
        sm[{3, Face::PosY}] = 1;

    // +X-blockZdiagonal -> top corner 2
    dy = blockY - yTransform(calculateNoise(blockX + 1, blockZ - 1));
    if (dy == -1)
        sm[{2, Face::PosY}] = 1;

    // -X+blockZdiagonal -> top corner 0
    dy = blockY - yTransform(calculateNoise(blockX - 1, blockZ + 1));
    if (dy == -1)
        sm[{0, Face::PosY}] = 1;

    // -X-blockZdiagonal -> top corner 1
    dy = blockY - yTransform(calculateNoise(blockX - 1, blockZ - 1));
    if (dy == -1)
        sm[{1, Face::PosY}] = 1;
}

void World::GenerateChunk(int chunkX, int chunkZ)
{
    Chunk chunk(chunkX, chunkZ);

    for (int x = 0; x < chunkSize; x++)
    {
        for (int z = 0; z < chunkSize; z++)
        {
            int xOffset = x + chunkSize * chunkX;
            int zOffset = z + chunkSize * chunkZ;
            int y = yTransform(calculateNoise(xOffset, zOffset));

            VertexShadingMap vertexShadingMap;
            ApplyShadingMap(vertexShadingMap, xOffset, y, zOffset);

            Cube c(glm::vec3(xOffset, y, zOffset), "./assets/grass.jpg", vertexShadingMap);
            chunk.objects.push_back(c);
        }
    }

    chunks.insert({chunk.coords, chunk});
}