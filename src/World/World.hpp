#pragma once
#include "Objects/Cube.hpp"
#include "Objects/Structures/Tree.hpp"
#include <random>
#include <unordered_map>

enum class Face {
    PosX,
    NegX,
    PosY,
    NegY,
    PosZ,
    NegZ
};

// Shading entries are keyed by (corner index, face) so the same corner can
// carry different values on each of the three faces that share it.
// instead of returning all of the objects attributes,
// each unique object is exposed once with a unique identifier.
// That way less data has to be sent to the engine, the cost of
// Cube creation is cut out and only data that changes is sent.

struct RawObject {
    glm::vec3 position;
    using VertexShadingMap = std::map<std::pair<int, Face>, int>;
    int id;
};

struct ChunkCoords {
    int x;
    int z;

    bool operator==(const ChunkCoords &c) const {
        return x == c.x && z == c.z;
    };
};

struct Chunk {
    ChunkCoords coords;
    Chunk(int _x, int _z) {
        coords.x = _x, coords.z = _z;
    };
    void PushMultiple(const std::vector<RawObject> _objects) {
        for (RawObject c : _objects) {
            objects.push_back(c);
        }
    };
    std::vector<RawObject> objects;
};

struct ChunkCoordHash {
    std::size_t operator()(const ChunkCoords &c) const noexcept {
        size_t hx = std::hash<int>{}(c.x);
        size_t hz = std::hash<int>{}(c.z);
        return hx ^ (hz * 2654435761u);
    }
};

const inline int renderDistance = 2; // Number of chunks to render in each direction
const inline int chunkSize = 100;

class World {
  private:
    std::unordered_map<int, Object> objectMap;
    std::unordered_map<ChunkCoords, Chunk, ChunkCoordHash> chunks; // Might actually be redundant because Chunk already holds Chunkcoords
    void GenerateChunk(int chunkX, int chunkZ);
    std::vector<Object> GetUniqueObjects(); // for instancing

  public:
    World();
    std::vector<RawObject> GetChunkObjectsForCameraPosition(double x, double z); // Theres def a better data struct for this as one id is represented multiple times
    std::vector<Object> GetObjects();
    std::pair<int, int> GetChunkCoordinatesFromCameraPosition(double x, double z);
    std::unordered_map<int, Object> GetObjectMapping();
};
