#pragma once
#include <random>
#include "World/Objects/Cube.hpp"
#include "../../includes/PerlinNoise.hpp"

// noise
std::random_device rd;
const siv::PerlinNoise::seed_type seed = rd();

const siv::PerlinNoise perlin{seed};
constexpr double calculateNoise(int x, int z) { return perlin.octave2D_01(((x + 20) * 0.005), ((z + 20) * 0.005), 4); }
constexpr int yTransform(double noise) { return -2.0f * noise * 30; }

class World
{
private:
    std::vector<Object> objects;
    void GenerateChunks();

public:
    World();
    std::vector<Object> GetObjects();
};