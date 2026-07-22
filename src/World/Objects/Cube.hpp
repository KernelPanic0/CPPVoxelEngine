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

struct VertexDesc {
    int corner; // -1 = center vertex, never shaded
    Face face;
};

static const VertexDesc vertexDescs[72] = {
    // -Z face (NegZ), vertices 0-11
    {6, Face::NegZ},
    {5, Face::NegZ},
    {-1, Face::NegZ},
    {5, Face::NegZ},
    {1, Face::NegZ},
    {-1, Face::NegZ},
    {1, Face::NegZ},
    {2, Face::NegZ},
    {-1, Face::NegZ},
    {2, Face::NegZ},
    {6, Face::NegZ},
    {-1, Face::NegZ},

    // +Z face (PosZ), vertices 12-23
    {4, Face::PosZ},
    {7, Face::PosZ},
    {-1, Face::PosZ},
    {7, Face::PosZ},
    {3, Face::PosZ},
    {-1, Face::PosZ},
    {3, Face::PosZ},
    {0, Face::PosZ},
    {-1, Face::PosZ},
    {0, Face::PosZ},
    {4, Face::PosZ},
    {-1, Face::PosZ},

    // -X face (NegX), vertices 24-35
    {0, Face::NegX},
    {1, Face::NegX},
    {-1, Face::NegX},
    {1, Face::NegX},
    {5, Face::NegX},
    {-1, Face::NegX},
    {5, Face::NegX},
    {4, Face::NegX},
    {-1, Face::NegX},
    {4, Face::NegX},
    {0, Face::NegX},
    {-1, Face::NegX},

    // +X face (PosX), vertices 36-47
    {3, Face::PosX},
    {7, Face::PosX},
    {-1, Face::PosX},
    {7, Face::PosX},
    {6, Face::PosX},
    {-1, Face::PosX},
    {6, Face::PosX},
    {2, Face::PosX},
    {-1, Face::PosX},
    {2, Face::PosX},
    {3, Face::PosX},
    {-1, Face::PosX},

    // -Y face (NegY), vertices 48-59
    {5, Face::NegY},
    {6, Face::NegY},
    {-1, Face::NegY},
    {6, Face::NegY},
    {7, Face::NegY},
    {-1, Face::NegY},
    {7, Face::NegY},
    {4, Face::NegY},
    {-1, Face::NegY},
    {4, Face::NegY},
    {5, Face::NegY},
    {-1, Face::NegY},

    // +Y face (PosY), vertices 60-71
    {2, Face::PosY},
    {1, Face::PosY},
    {-1, Face::PosY},
    {1, Face::PosY},
    {0, Face::PosY},
    {-1, Face::PosY},
    {0, Face::PosY},
    {3, Face::PosY},
    {-1, Face::PosY},
    {3, Face::PosY},
    {2, Face::PosY},
    {-1, Face::PosY},
};

class Cube : public Object {
  public:
    Cube(glm::vec3 position, std::string texturePath = "");

    // Cube corners are indexed 0-7 (see Cube.cpp for the layout).
    static void ApplyShadingMap(VertexShadingMap &sm, glm::vec3 position);
    static std::vector<float> ShadingMapToFlatArray(const VertexShadingMap &sm);
};