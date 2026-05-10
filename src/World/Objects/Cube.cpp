#include "Cube.hpp"

Cube::Cube(glm::vec3 position, std::string _texturePath, std::map<int, VertexShading> vertexShadingMap)
{
    // Returns the shading value for cube corner v, but only when the entry's
    // face matches f. Different faces sharing that corner read 0 instead.
    auto vs = [&](int v, Face f) -> int {
        auto it = vertexShadingMap.find(v);
        return (it != vertexShadingMap.end() && it->second.face == f) ? it->second.value : 0;
    };

    // Cube corners (see Cube.hpp): 0..3 top (front-left, back-left, back-right, front-right),
    //                              4..7 bottom (same order).
    // clang-format off
    std::vector<float> verticesT = {
        // Position          // Texture     // Normal            // Shading Value
        // -Z (back) face — corners 1, 2, 5, 6
        -0.5f, -0.5f, -0.5f,  0.5f, 0.25f,   0.0f,  0.0f, -1.0f, (float)vs(5, Face::NegZ),
        0.5f,  0.5f, -0.5f,  0.25f, 0.75f,   0.0f,  0.0f, -1.0f, (float)vs(2, Face::NegZ),
        0.5f, -0.5f, -0.5f,  0.25f, 0.25f,   0.0f,  0.0f, -1.0f, (float)vs(6, Face::NegZ),
        -0.5f, -0.5f, -0.5f,  0.5f, 0.25f,   0.0f,  0.0f, -1.0f, (float)vs(5, Face::NegZ),
        -0.5f,  0.5f, -0.5f,  0.5f, 0.75f,   0.0f,  0.0f, -1.0f, (float)vs(1, Face::NegZ),
        0.5f,  0.5f, -0.5f,  0.25f, 0.75f,   0.0f,  0.0f, -1.0f, (float)vs(2, Face::NegZ),

        // +Z (front) face — corners 0, 3, 4, 7
        -0.5f, -0.5f,  0.5f,  0.5f, 0.25f,   0.0f,  0.0f,  1.0f, (float)vs(4, Face::PosZ),
        0.5f, -0.5f,  0.5f,  0.25f, 0.25f,   0.0f,  0.0f,  1.0f, (float)vs(7, Face::PosZ),
        0.5f,  0.5f,  0.5f,  0.25f, 0.75f,   0.0f,  0.0f,  1.0f, (float)vs(3, Face::PosZ),
        0.5f,  0.5f,  0.5f,  0.25f, 0.75f,   0.0f,  0.0f,  1.0f, (float)vs(3, Face::PosZ),
        -0.5f,  0.5f,  0.5f,  0.5f, 0.75f,   0.0f,  0.0f,  1.0f, (float)vs(0, Face::PosZ),
        -0.5f, -0.5f,  0.5f,  0.5f, 0.25f,   0.0f,  0.0f,  1.0f, (float)vs(4, Face::PosZ),

        // -X (left) face — corners 0, 1, 4, 5
        -0.5f,  0.5f,  0.5f,  0.25f, 0.75f, -1.0f,  0.0f,  0.0f, (float)vs(0, Face::NegX),
        -0.5f,  0.5f, -0.5f,  0.5f, 0.75f,  -1.0f,  0.0f,  0.0f, (float)vs(1, Face::NegX),
        -0.5f, -0.5f, -0.5f,  0.5f, 0.25f,  -1.0f,  0.0f,  0.0f, (float)vs(5, Face::NegX),
        -0.5f, -0.5f, -0.5f,  0.5f, 0.25f,  -1.0f,  0.0f,  0.0f, (float)vs(5, Face::NegX),
        -0.5f, -0.5f,  0.5f,  0.25f, 0.25f, -1.0f,  0.0f,  0.0f, (float)vs(4, Face::NegX),
        -0.5f,  0.5f,  0.5f,  0.25f, 0.75f, -1.0f,  0.0f,  0.0f, (float)vs(0, Face::NegX),

        // +X (right) face — corners 2, 3, 6, 7
        0.5f,  0.5f,  0.5f,  0.5f,  0.75f,  1.0f,  0.0f,  0.0f, (float)vs(3, Face::PosX),
        0.5f, -0.5f, -0.5f,  0.25f, 0.25f,  1.0f,  0.0f,  0.0f, (float)vs(6, Face::PosX),
        0.5f,  0.5f, -0.5f,  0.25f, 0.75f,  1.0f,  0.0f,  0.0f, (float)vs(2, Face::PosX),
        0.5f,  0.5f,  0.5f,  0.5f,  0.75f,  1.0f,  0.0f,  0.0f, (float)vs(3, Face::PosX),
        0.5f, -0.5f,  0.5f,  0.5f,  0.25f,  1.0f,  0.0f,  0.0f, (float)vs(7, Face::PosX),
        0.5f, -0.5f, -0.5f,  0.25f, 0.25f,  1.0f,  0.0f,  0.0f, (float)vs(6, Face::PosX),

        // -Y (bottom) face — corners 4, 5, 6, 7
        -0.5f, -0.5f, -0.5f,  0.25f, 0.0f,   0.0f, -1.0f,  0.0f, (float)vs(5, Face::NegY),
        0.5f, -0.5f, -0.5f,  0.25f, 0.25f,   0.0f, -1.0f,  0.0f, (float)vs(6, Face::NegY),
        0.5f, -0.5f,  0.5f,  0.5f, 0.25f,    0.0f, -1.0f,  0.0f, (float)vs(7, Face::NegY),
        0.5f, -0.5f,  0.5f,  0.5f, 0.25f,    0.0f, -1.0f,  0.0f, (float)vs(7, Face::NegY),
        -0.5f, -0.5f,  0.5f,  0.5f, 0.0f,    0.0f, -1.0f,  0.0f, (float)vs(4, Face::NegY),
        -0.5f, -0.5f, -0.5f,  0.25f, 0.0f,   0.0f, -1.0f,  0.0f, (float)vs(5, Face::NegY),

        // +Y (top) face — corners 0, 1, 2, 3
        -0.5f,  0.5f, -0.5f,  0.25f, 0.75f,  0.0f,  1.0f,  0.0f, (float)vs(1, Face::PosY),
        0.5f,  0.5f,  0.5f,  0.5f,  1.0f,    0.0f,  1.0f,  0.0f, (float)vs(3, Face::PosY),
        0.5f,  0.5f, -0.5f,  0.25f, 1.0f,    0.0f,  1.0f,  0.0f, (float)vs(2, Face::PosY),
        -0.5f,  0.5f, -0.5f,  0.25f, 0.75f,  0.0f,  1.0f,  0.0f, (float)vs(1, Face::PosY),
        -0.5f,  0.5f,  0.5f,  0.5f,  0.75f,  0.0f,  1.0f,  0.0f, (float)vs(0, Face::PosY),
        0.5f,  0.5f,  0.5f,  0.5f,  1.0f,    0.0f,  1.0f,  0.0f, (float)vs(3, Face::PosY),
    };

    std::vector<int> indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // clang-format on

    Mesh cubeMesh = {verticesT, indices};
    ObjectAttribute positionAttr = {3, GL_FLOAT, sizeof(float)};
    ObjectAttribute textureCoordinatesAttr = {2, GL_FLOAT, sizeof(float)};
    ObjectAttribute surfaceNormalAttr = {3, GL_FLOAT, sizeof(float)};
    ObjectAttribute vertexShadingAttr = {1, GL_FLOAT, sizeof(float)};

    this->mesh = cubeMesh;
    this->attributes = {positionAttr, textureCoordinatesAttr, surfaceNormalAttr, vertexShadingAttr};
    this->position = position;
    this->texturePath = _texturePath;
}
