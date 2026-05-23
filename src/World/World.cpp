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

void World::GenerateChunk(int chunkX, int chunkZ)
{
    Chunk chunk(chunkX, chunkZ);
    bool hasTree = std::rand() <= 429496729;

    for (int x = 0; x < chunkSize; x++)
    {
        for (int z = 0; z < chunkSize; z++)
        {
            int xOffset = x + chunkSize * chunkX;
            int zOffset = z + chunkSize * chunkZ;
            int y = Settings::yTransform(Settings::calculateNoise(xOffset, zOffset));

            Cube c(glm::vec3(xOffset, y, zOffset), "./assets/grass.png");
            chunk.objects.push_back(c);
        }
    }

    // Currently there is a bug where the tree's AO is accurate respective to its surrounding blocks, but the surrounding blocks' AO isn't. This is because the tree is generated after the blocks
    if (hasTree)
    {
        Tree t(glm::vec3(chunk.objects[0].position.x, chunk.objects[0].position.y + 1, chunk.objects[0].position.z));
        chunk.PushMultiple(t.objects);
    }

    chunks.insert({chunk.coords, chunk});
}