#pragma once
#include <random>
#include <unordered_map>
#include "World/Objects/Cube.hpp"
#include "World/Objects/Structures/Tree.hpp"

struct ChunkCoords
{
    int x;
    int z;

    bool operator==(const ChunkCoords &c) const { return x == c.x && z == c.z; };
};

struct Chunk
{
    ChunkCoords coords;
    Chunk(int _x, int _z) { coords.x = _x, coords.z = _z; };
    void PushMultiple(const std::vector<Cube> _objects)
    {
        for (Cube c : _objects)
        {
            objects.push_back(c);
        }
    };
    std::vector<Cube> objects;
};

struct ChunkCoordHash
{
    std::size_t operator()(const ChunkCoords &c) const noexcept
    {
        size_t hx = std::hash<int>{}(c.x);
        size_t hz = std::hash<int>{}(c.z);
        return hx ^ (hz * 2654435761u);
    }
};

const inline int renderDistance = 2; // Number of chunks to render in each direction
const inline int chunkSize = 16;

class World
{
private:
    std::unordered_map<ChunkCoords, Chunk, ChunkCoordHash> chunks; // Might actually be redundant because Chunk already holds Chunkcoords
    void GenerateChunk(int chunkX, int chunkZ);

public:
    World();
    std::vector<Object> GetChunkObjectsForCameraPosition(double x, double z);
    std::vector<Object> GetObjects();
    std::pair<int, int> GetChunkCoordinatesFromCameraPosition(double x, double z);
};