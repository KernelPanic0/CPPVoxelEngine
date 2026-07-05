#pragma once
#include "../../Engine/Graphics/Mesh.hpp"
#include "Object.hpp"
#include "map"

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
using VertexShadingMap = std::map<std::pair<int, Face>, int>;

class Cube : public Object {
  public:
    Cube(glm::vec3 position, std::string texturePath = "");

    // Cube corners are indexed 0-7 (see Cube.cpp for the layout).
    static void ApplyShadingMap(VertexShadingMap &sm, glm::vec3 position);
};
