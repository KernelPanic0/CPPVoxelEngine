#pragma once
#include "../../Graphics/Mesh.hpp"
#include "Object.hpp"
#include "map"

enum class Face { PosX, NegX, PosY, NegY, PosZ, NegZ };

// Shading entry for a single cube corner. `value` is only applied when rendering
// `face`; the other two faces sharing that corner are unaffected.
struct VertexShading
{
    Face face = Face::PosX;
    int value = 0;
};

class Cube : public Object
{
public:
    // Cube corners are indexed 0-7 (see Cube.cpp for the layout).
    Cube(glm::vec3 position, std::string texturePath = "", std::map<int, VertexShading> vertexShadingMap = {});
};
