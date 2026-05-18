#pragma once
#include <random>
#include <unordered_map>
#include "World/Objects/Cube.hpp"
#include "../../includes/PerlinNoise.hpp"

// noise
inline std::random_device rd;
const siv::PerlinNoise::seed_type seed = rd();

const siv::PerlinNoise perlin{seed};
constexpr double calculateNoise(int x, int z) { return perlin.octave2D_01(((x + 20) * 0.005), ((z + 20) * 0.005), 4); }
constexpr int yTransform(double noise) { return -2.0f * noise * 30; }

struct ChunkCoords
{
    int x;
    int z;

    bool operator==(const ChunkCoords &c) const { return x == c.x && z == c.z; };
};

struct Chunk
{
    ChunkCoords coords;
    Chunk(int _x, int _z) { coords.x = _x,
                            coords.z = _z; };
    std::vector<Object> objects;
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

class World
{
private:
    std::unordered_map<ChunkCoords, Chunk, ChunkCoordHash> chunks; // Might actually be redundant because Chunk already holds Chunkcoords
    // std::map<std::pair<int, int>, Object> chunkObjects; // chunkx, chunkz, and the associated chunk
    void GenerateChunks(int chunkX, int chunkZ, int chunkXC, int chunkZC);
    int renderDistance = 10;
    int chunkSize = 10;

public:
    World();
    Chunk GetChunksForCameraPosition(int x, int z);
    std::vector<Object> GetObjects();
};