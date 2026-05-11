#include "Cube.hpp"

Cube::Cube(glm::vec3 position, std::string _texturePath, VertexShadingMap vertexShadingMap)
{
    auto vs = [&](int v, Face f) -> int {
        auto it = vertexShadingMap.find({v, f});
        return (it != vertexShadingMap.end()) ? it->second : 0;
    };

    // Each face is split into 4 triangles fanning around a center vertex whose
    // shading is the average of its 4 corner shadings. With the naive 2-triangle
    // split, gouraud interpolation smears shading from the two corners on the
    // diagonal seam (e.g. v1↔v3 on the top face) toward the opposite corner; the
    // fan layout makes every corner symmetric.
    auto avg4 = [](int a, int b, int c, int d) { return (a + b + c + d) / 4.0f; };

    float cNegZ = avg4(vs(5, Face::NegZ), vs(6, Face::NegZ), vs(2, Face::NegZ), vs(1, Face::NegZ));
    float cPosZ = avg4(vs(4, Face::PosZ), vs(7, Face::PosZ), vs(3, Face::PosZ), vs(0, Face::PosZ));
    float cNegX = avg4(vs(0, Face::NegX), vs(1, Face::NegX), vs(5, Face::NegX), vs(4, Face::NegX));
    float cPosX = avg4(vs(3, Face::PosX), vs(7, Face::PosX), vs(6, Face::PosX), vs(2, Face::PosX));
    float cNegY = avg4(vs(5, Face::NegY), vs(6, Face::NegY), vs(7, Face::NegY), vs(4, Face::NegY));
    float cPosY = avg4(vs(1, Face::PosY), vs(3, Face::PosY), vs(2, Face::PosY), vs(0, Face::PosY));

    // Cube corners (see Cube.hpp): 0..3 top (front-left, back-left, back-right, front-right),
    //                              4..7 bottom (same order).
    // clang-format off
    std::vector<float> verticesT = {
        // Position           // Texture        // Normal             // Shading

        // -Z (back) face — perimeter v6 → v5 → v1 → v2, center at (0, 0, -0.5)
         0.5f, -0.5f, -0.5f,  0.25f,  0.25f,    0.0f,  0.0f, -1.0f,  (float)vs(6, Face::NegZ),
        -0.5f, -0.5f, -0.5f,  0.5f,   0.25f,    0.0f,  0.0f, -1.0f,  (float)vs(5, Face::NegZ),
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,  cNegZ,

        -0.5f, -0.5f, -0.5f,  0.5f,   0.25f,    0.0f,  0.0f, -1.0f,  (float)vs(5, Face::NegZ),
        -0.5f,  0.5f, -0.5f,  0.5f,   0.75f,    0.0f,  0.0f, -1.0f,  (float)vs(1, Face::NegZ),
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,  cNegZ,

        -0.5f,  0.5f, -0.5f,  0.5f,   0.75f,    0.0f,  0.0f, -1.0f,  (float)vs(1, Face::NegZ),
         0.5f,  0.5f, -0.5f,  0.25f,  0.75f,    0.0f,  0.0f, -1.0f,  (float)vs(2, Face::NegZ),
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,  cNegZ,

         0.5f,  0.5f, -0.5f,  0.25f,  0.75f,    0.0f,  0.0f, -1.0f,  (float)vs(2, Face::NegZ),
         0.5f, -0.5f, -0.5f,  0.25f,  0.25f,    0.0f,  0.0f, -1.0f,  (float)vs(6, Face::NegZ),
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,  cNegZ,

        // +Z (front) face — perimeter v4 → v7 → v3 → v0, center at (0, 0, 0.5)
        -0.5f, -0.5f,  0.5f,  0.5f,   0.25f,    0.0f,  0.0f,  1.0f,  (float)vs(4, Face::PosZ),
         0.5f, -0.5f,  0.5f,  0.25f,  0.25f,    0.0f,  0.0f,  1.0f,  (float)vs(7, Face::PosZ),
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,  cPosZ,

         0.5f, -0.5f,  0.5f,  0.25f,  0.25f,    0.0f,  0.0f,  1.0f,  (float)vs(7, Face::PosZ),
         0.5f,  0.5f,  0.5f,  0.25f,  0.75f,    0.0f,  0.0f,  1.0f,  (float)vs(3, Face::PosZ),
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,  cPosZ,

         0.5f,  0.5f,  0.5f,  0.25f,  0.75f,    0.0f,  0.0f,  1.0f,  (float)vs(3, Face::PosZ),
        -0.5f,  0.5f,  0.5f,  0.5f,   0.75f,    0.0f,  0.0f,  1.0f,  (float)vs(0, Face::PosZ),
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,  cPosZ,

        -0.5f,  0.5f,  0.5f,  0.5f,   0.75f,    0.0f,  0.0f,  1.0f,  (float)vs(0, Face::PosZ),
        -0.5f, -0.5f,  0.5f,  0.5f,   0.25f,    0.0f,  0.0f,  1.0f,  (float)vs(4, Face::PosZ),
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,  cPosZ,

        // -X (left) face — perimeter v0 → v1 → v5 → v4, center at (-0.5, 0, 0)
        -0.5f,  0.5f,  0.5f,  0.25f,  0.75f,   -1.0f,  0.0f,  0.0f,  (float)vs(0, Face::NegX),
        -0.5f,  0.5f, -0.5f,  0.5f,   0.75f,   -1.0f,  0.0f,  0.0f,  (float)vs(1, Face::NegX),
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,  cNegX,

        -0.5f,  0.5f, -0.5f,  0.5f,   0.75f,   -1.0f,  0.0f,  0.0f,  (float)vs(1, Face::NegX),
        -0.5f, -0.5f, -0.5f,  0.5f,   0.25f,   -1.0f,  0.0f,  0.0f,  (float)vs(5, Face::NegX),
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,  cNegX,

        -0.5f, -0.5f, -0.5f,  0.5f,   0.25f,   -1.0f,  0.0f,  0.0f,  (float)vs(5, Face::NegX),
        -0.5f, -0.5f,  0.5f,  0.25f,  0.25f,   -1.0f,  0.0f,  0.0f,  (float)vs(4, Face::NegX),
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,  cNegX,

        -0.5f, -0.5f,  0.5f,  0.25f,  0.25f,   -1.0f,  0.0f,  0.0f,  (float)vs(4, Face::NegX),
        -0.5f,  0.5f,  0.5f,  0.25f,  0.75f,   -1.0f,  0.0f,  0.0f,  (float)vs(0, Face::NegX),
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,  cNegX,

        // +X (right) face — perimeter v3 → v7 → v6 → v2, center at (0.5, 0, 0)
         0.5f,  0.5f,  0.5f,  0.5f,   0.75f,    1.0f,  0.0f,  0.0f,  (float)vs(3, Face::PosX),
         0.5f, -0.5f,  0.5f,  0.5f,   0.25f,    1.0f,  0.0f,  0.0f,  (float)vs(7, Face::PosX),
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,  cPosX,

         0.5f, -0.5f,  0.5f,  0.5f,   0.25f,    1.0f,  0.0f,  0.0f,  (float)vs(7, Face::PosX),
         0.5f, -0.5f, -0.5f,  0.25f,  0.25f,    1.0f,  0.0f,  0.0f,  (float)vs(6, Face::PosX),
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,  cPosX,

         0.5f, -0.5f, -0.5f,  0.25f,  0.25f,    1.0f,  0.0f,  0.0f,  (float)vs(6, Face::PosX),
         0.5f,  0.5f, -0.5f,  0.25f,  0.75f,    1.0f,  0.0f,  0.0f,  (float)vs(2, Face::PosX),
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,  cPosX,

         0.5f,  0.5f, -0.5f,  0.25f,  0.75f,    1.0f,  0.0f,  0.0f,  (float)vs(2, Face::PosX),
         0.5f,  0.5f,  0.5f,  0.5f,   0.75f,    1.0f,  0.0f,  0.0f,  (float)vs(3, Face::PosX),
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,  cPosX,

        // -Y (bottom) face — perimeter v5 → v6 → v7 → v4, center at (0, -0.5, 0)
        -0.5f, -0.5f, -0.5f,  0.25f,  0.0f,     0.0f, -1.0f,  0.0f,  (float)vs(5, Face::NegY),
         0.5f, -0.5f, -0.5f,  0.25f,  0.25f,    0.0f, -1.0f,  0.0f,  (float)vs(6, Face::NegY),
         0.0f, -0.5f,  0.0f,  0.375f, 0.125f,   0.0f, -1.0f,  0.0f,  cNegY,

         0.5f, -0.5f, -0.5f,  0.25f,  0.25f,    0.0f, -1.0f,  0.0f,  (float)vs(6, Face::NegY),
         0.5f, -0.5f,  0.5f,  0.5f,   0.25f,    0.0f, -1.0f,  0.0f,  (float)vs(7, Face::NegY),
         0.0f, -0.5f,  0.0f,  0.375f, 0.125f,   0.0f, -1.0f,  0.0f,  cNegY,

         0.5f, -0.5f,  0.5f,  0.5f,   0.25f,    0.0f, -1.0f,  0.0f,  (float)vs(7, Face::NegY),
        -0.5f, -0.5f,  0.5f,  0.5f,   0.0f,     0.0f, -1.0f,  0.0f,  (float)vs(4, Face::NegY),
         0.0f, -0.5f,  0.0f,  0.375f, 0.125f,   0.0f, -1.0f,  0.0f,  cNegY,

        -0.5f, -0.5f,  0.5f,  0.5f,   0.0f,     0.0f, -1.0f,  0.0f,  (float)vs(4, Face::NegY),
        -0.5f, -0.5f, -0.5f,  0.25f,  0.0f,     0.0f, -1.0f,  0.0f,  (float)vs(5, Face::NegY),
         0.0f, -0.5f,  0.0f,  0.375f, 0.125f,   0.0f, -1.0f,  0.0f,  cNegY,

        // +Y (top) face — perimeter v2 → v1 → v0 → v3, center at (0, 0.5, 0)
         0.5f,  0.5f, -0.5f,  0.25f,  1.0f,     0.0f,  1.0f,  0.0f,  (float)vs(2, Face::PosY),
        -0.5f,  0.5f, -0.5f,  0.25f,  0.75f,    0.0f,  1.0f,  0.0f,  (float)vs(1, Face::PosY),
         0.0f,  0.5f,  0.0f,  0.375f, 0.875f,   0.0f,  1.0f,  0.0f,  cPosY,

        -0.5f,  0.5f, -0.5f,  0.25f,  0.75f,    0.0f,  1.0f,  0.0f,  (float)vs(1, Face::PosY),
        -0.5f,  0.5f,  0.5f,  0.5f,   0.75f,    0.0f,  1.0f,  0.0f,  (float)vs(0, Face::PosY),
         0.0f,  0.5f,  0.0f,  0.375f, 0.875f,   0.0f,  1.0f,  0.0f,  cPosY,

        -0.5f,  0.5f,  0.5f,  0.5f,   0.75f,    0.0f,  1.0f,  0.0f,  (float)vs(0, Face::PosY),
         0.5f,  0.5f,  0.5f,  0.5f,   1.0f,     0.0f,  1.0f,  0.0f,  (float)vs(3, Face::PosY),
         0.0f,  0.5f,  0.0f,  0.375f, 0.875f,   0.0f,  1.0f,  0.0f,  cPosY,

         0.5f,  0.5f,  0.5f,  0.5f,   1.0f,     0.0f,  1.0f,  0.0f,  (float)vs(3, Face::PosY),
         0.5f,  0.5f, -0.5f,  0.25f,  1.0f,     0.0f,  1.0f,  0.0f,  (float)vs(2, Face::PosY),
         0.0f,  0.5f,  0.0f,  0.375f, 0.875f,   0.0f,  1.0f,  0.0f,  cPosY,
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
