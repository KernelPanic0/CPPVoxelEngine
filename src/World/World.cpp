#include "World.hpp"

World::World() {
    std::vector<Object> uniqueObjects = GetUniqueObjects();

    for (int i = 0; i < uniqueObjects.size(); i++) {
        objectMap[i] = uniqueObjects[i];
    }

    GenerateChunk(0, 0);
}

std::pair<int, int> World::GetChunkCoordinatesFromCameraPosition(double x, double z) {
    int currentChunkX = static_cast<int>(std::floor(x / chunkSize));
    int currentChunkZ = static_cast<int>(std::floor(z / chunkSize));

    return {currentChunkX, currentChunkZ};
}

std::vector<RawObject> World::GetChunkObjectsForCameraPosition(double x, double z) {
    auto [currentChunkX, currentChunkZ] = GetChunkCoordinatesFromCameraPosition(x, z);
    std::vector<RawObject> objects;

    for (int dx = -renderDistance; dx < renderDistance; dx++) {
        for (int dz = -renderDistance; dz < renderDistance; dz++) {
            int chunkX = currentChunkX + dx;
            int chunkZ = currentChunkZ + dz;

            GenerateChunk(chunkX, chunkZ);

            auto it = chunks.find({chunkX, chunkZ});
            if (it != chunks.end()) {
                for (RawObject obj : it->second.objects) {
                    objects.push_back(obj);
                }
            } else {
                for (RawObject obj : Chunk(chunkX, chunkZ).objects) {
                    objects.push_back(obj);
                }
            }
        }
    }

    return objects;
}

void World::GenerateChunk(int chunkX, int chunkZ) {
    Chunk chunk(chunkX, chunkZ);
    bool hasTree = std::rand() <= 429496729; // randomly decide whether tree should be generated

    for (int x = 0; x < chunkSize; x++) {
        for (int z = 0; z < chunkSize; z++) {
            int xOffset = x + chunkSize * chunkX;
            int zOffset = z + chunkSize * chunkZ;
            int y = Settings::yTransform(Settings::calculateNoise(xOffset, zOffset));

            chunk.objects.emplace_back(glm::vec3(xOffset, y, zOffset), 0);
        }
    }

    // Currently there is a bug where the tree's AO is accurate respective to its surrounding blocks, but the surrounding blocks' AO isn't. This is because the tree is generated after the blocks
    // tree will be figured out later sorry
    // if (hasTree) {
    //     Tree t(glm::vec3(chunk.objects[0].position.x, chunk.objects[0].position.y + 1, chunk.objects[0].position.z));
    //     chunk.PushMultiple(t.objects);
    // }

    chunks.insert({chunk.coords, chunk});
}

std::vector<Object> World::GetUniqueObjects() {
    std::vector<Object> objects;
    objects.push_back(Cube(glm::vec3(0, 0, 0), "./assets/grass2.png"));

    return objects;
}

std::unordered_map<int, Object> World::GetObjectMapping() { // for instancing
    return objectMap;
}