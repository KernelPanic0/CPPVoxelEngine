#include "Cube.hpp"

Cube::Cube(glm::vec3 position, std::string _texturePath) {
    VertexShadingMap vertexShadingMap;
    ApplyShadingMap(vertexShadingMap, position);

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
    // Texture is a 4:3 cross unfolding (4 cells wide x 3 cells tall)
    // y is 0 or 1/3 for bottom face, 1/3 or 2/3 for side faces, 2/3 or 1 for top face

    constexpr float sLo = 1.0f / 3.0f;
    constexpr float sHi = 2.0f / 3.0f;
    constexpr float bCtr = 1.0f / 6.0f;
    constexpr float tCtr = 5.0f / 6.0f;
    // clang-format off
    std::vector<float> verticesT = {
        // Position           // Texture        // Normal             // Shading

        // -Z (back) face — perimeter v6 → v5 → v1 → v2, center at (0, 0, -0.5)
         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      0.0f,  0.0f, -1.0f,  (float)vs(6, Face::NegZ),
        -0.5f, -0.5f, -0.5f,  0.5f,   sLo,      0.0f,  0.0f, -1.0f,  (float)vs(5, Face::NegZ),
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,  cNegZ,

        -0.5f, -0.5f, -0.5f,  0.5f,   sLo,      0.0f,  0.0f, -1.0f,  (float)vs(5, Face::NegZ),
        -0.5f,  0.5f, -0.5f,  0.5f,   sHi,      0.0f,  0.0f, -1.0f,  (float)vs(1, Face::NegZ),
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,  cNegZ,

        -0.5f,  0.5f, -0.5f,  0.5f,   sHi,      0.0f,  0.0f, -1.0f,  (float)vs(1, Face::NegZ),
         0.5f,  0.5f, -0.5f,  0.25f,  sHi,      0.0f,  0.0f, -1.0f,  (float)vs(2, Face::NegZ),
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,  cNegZ,

         0.5f,  0.5f, -0.5f,  0.25f,  sHi,      0.0f,  0.0f, -1.0f,  (float)vs(2, Face::NegZ),
         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      0.0f,  0.0f, -1.0f,  (float)vs(6, Face::NegZ),
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,  cNegZ,

        // +Z (front) face — perimeter v4 → v7 → v3 → v0, center at (0, 0, 0.5)
        -0.5f, -0.5f,  0.5f,  0.5f,   sLo,      0.0f,  0.0f,  1.0f,  (float)vs(4, Face::PosZ),
         0.5f, -0.5f,  0.5f,  0.25f,  sLo,      0.0f,  0.0f,  1.0f,  (float)vs(7, Face::PosZ),
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,  cPosZ,

         0.5f, -0.5f,  0.5f,  0.25f,  sLo,      0.0f,  0.0f,  1.0f,  (float)vs(7, Face::PosZ),
         0.5f,  0.5f,  0.5f,  0.25f,  sHi,      0.0f,  0.0f,  1.0f,  (float)vs(3, Face::PosZ),
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,  cPosZ,

         0.5f,  0.5f,  0.5f,  0.25f,  sHi,      0.0f,  0.0f,  1.0f,  (float)vs(3, Face::PosZ),
        -0.5f,  0.5f,  0.5f,  0.5f,   sHi,      0.0f,  0.0f,  1.0f,  (float)vs(0, Face::PosZ),
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,  cPosZ,

        -0.5f,  0.5f,  0.5f,  0.5f,   sHi,      0.0f,  0.0f,  1.0f,  (float)vs(0, Face::PosZ),
        -0.5f, -0.5f,  0.5f,  0.5f,   sLo,      0.0f,  0.0f,  1.0f,  (float)vs(4, Face::PosZ),
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,  cPosZ,

        // -X (left) face — perimeter v0 → v1 → v5 → v4, center at (-0.5, 0, 0)
        -0.5f,  0.5f,  0.5f,  0.25f,  sHi,     -1.0f,  0.0f,  0.0f,  (float)vs(0, Face::NegX),
        -0.5f,  0.5f, -0.5f,  0.5f,   sHi,     -1.0f,  0.0f,  0.0f,  (float)vs(1, Face::NegX),
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,  cNegX,

        -0.5f,  0.5f, -0.5f,  0.5f,   sHi,     -1.0f,  0.0f,  0.0f,  (float)vs(1, Face::NegX),
        -0.5f, -0.5f, -0.5f,  0.5f,   sLo,     -1.0f,  0.0f,  0.0f,  (float)vs(5, Face::NegX),
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,  cNegX,

        -0.5f, -0.5f, -0.5f,  0.5f,   sLo,     -1.0f,  0.0f,  0.0f,  (float)vs(5, Face::NegX),
        -0.5f, -0.5f,  0.5f,  0.25f,  sLo,     -1.0f,  0.0f,  0.0f,  (float)vs(4, Face::NegX),
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,  cNegX,

        -0.5f, -0.5f,  0.5f,  0.25f,  sLo,     -1.0f,  0.0f,  0.0f,  (float)vs(4, Face::NegX),
        -0.5f,  0.5f,  0.5f,  0.25f,  sHi,     -1.0f,  0.0f,  0.0f,  (float)vs(0, Face::NegX),
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,  cNegX,

        // +X (right) face — perimeter v3 → v7 → v6 → v2, center at (0.5, 0, 0)
         0.5f,  0.5f,  0.5f,  0.5f,   sHi,      1.0f,  0.0f,  0.0f,  (float)vs(3, Face::PosX),
         0.5f, -0.5f,  0.5f,  0.5f,   sLo,      1.0f,  0.0f,  0.0f,  (float)vs(7, Face::PosX),
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,  cPosX,

         0.5f, -0.5f,  0.5f,  0.5f,   sLo,      1.0f,  0.0f,  0.0f,  (float)vs(7, Face::PosX),
         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      1.0f,  0.0f,  0.0f,  (float)vs(6, Face::PosX),
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,  cPosX,

         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      1.0f,  0.0f,  0.0f,  (float)vs(6, Face::PosX),
         0.5f,  0.5f, -0.5f,  0.25f,  sHi,      1.0f,  0.0f,  0.0f,  (float)vs(2, Face::PosX),
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,  cPosX,

         0.5f,  0.5f, -0.5f,  0.25f,  sHi,      1.0f,  0.0f,  0.0f,  (float)vs(2, Face::PosX),
         0.5f,  0.5f,  0.5f,  0.5f,   sHi,      1.0f,  0.0f,  0.0f,  (float)vs(3, Face::PosX),
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,  cPosX,

        // -Y (bottom) face — perimeter v5 → v6 → v7 → v4, center at (0, -0.5, 0)
        -0.5f, -0.5f, -0.5f,  0.25f,  0.0f,     0.0f, -1.0f,  0.0f,  (float)vs(5, Face::NegY),
         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      0.0f, -1.0f,  0.0f,  (float)vs(6, Face::NegY),
         0.0f, -0.5f,  0.0f,  0.375f, bCtr,     0.0f, -1.0f,  0.0f,  cNegY,

         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      0.0f, -1.0f,  0.0f,  (float)vs(6, Face::NegY),
         0.5f, -0.5f,  0.5f,  0.5f,   sLo,      0.0f, -1.0f,  0.0f,  (float)vs(7, Face::NegY),
         0.0f, -0.5f,  0.0f,  0.375f, bCtr,     0.0f, -1.0f,  0.0f,  cNegY,

         0.5f, -0.5f,  0.5f,  0.5f,   sLo,      0.0f, -1.0f,  0.0f,  (float)vs(7, Face::NegY),
        -0.5f, -0.5f,  0.5f,  0.5f,   0.0f,     0.0f, -1.0f,  0.0f,  (float)vs(4, Face::NegY),
         0.0f, -0.5f,  0.0f,  0.375f, bCtr,     0.0f, -1.0f,  0.0f,  cNegY,

        -0.5f, -0.5f,  0.5f,  0.5f,   0.0f,     0.0f, -1.0f,  0.0f,  (float)vs(4, Face::NegY),
        -0.5f, -0.5f, -0.5f,  0.25f,  0.0f,     0.0f, -1.0f,  0.0f,  (float)vs(5, Face::NegY),
         0.0f, -0.5f,  0.0f,  0.375f, bCtr,     0.0f, -1.0f,  0.0f,  cNegY,

        // +Y (top) face — perimeter v2 → v1 → v0 → v3, center at (0, 0.5, 0)
         0.5f,  0.5f, -0.5f,  0.25f,  1.0f,     0.0f,  1.0f,  0.0f,  (float)vs(2, Face::PosY),
        -0.5f,  0.5f, -0.5f,  0.25f,  sHi,      0.0f,  1.0f,  0.0f,  (float)vs(1, Face::PosY),
         0.0f,  0.5f,  0.0f,  0.375f, tCtr,     0.0f,  1.0f,  0.0f,  cPosY,

        -0.5f,  0.5f, -0.5f,  0.25f,  sHi,      0.0f,  1.0f,  0.0f,  (float)vs(1, Face::PosY),
        -0.5f,  0.5f,  0.5f,  0.5f,   sHi,      0.0f,  1.0f,  0.0f,  (float)vs(0, Face::PosY),
         0.0f,  0.5f,  0.0f,  0.375f, tCtr,     0.0f,  1.0f,  0.0f,  cPosY,

        -0.5f,  0.5f,  0.5f,  0.5f,   sHi,      0.0f,  1.0f,  0.0f,  (float)vs(0, Face::PosY),
         0.5f,  0.5f,  0.5f,  0.5f,   1.0f,     0.0f,  1.0f,  0.0f,  (float)vs(3, Face::PosY),
         0.0f,  0.5f,  0.0f,  0.375f, tCtr,     0.0f,  1.0f,  0.0f,  cPosY,

         0.5f,  0.5f,  0.5f,  0.5f,   1.0f,     0.0f,  1.0f,  0.0f,  (float)vs(3, Face::PosY),
         0.5f,  0.5f, -0.5f,  0.25f,  1.0f,     0.0f,  1.0f,  0.0f,  (float)vs(2, Face::PosY),
         0.0f,  0.5f,  0.0f,  0.375f, tCtr,     0.0f,  1.0f,  0.0f,  cPosY,
    };

    // 8 floats per vertex: pos(3), uv(2), normal(3), shade(1)
    // verticesT already stores triangles in order, so create a linear index buffer.
    std::vector<int> indices;
    indices.reserve(verticesT.size() / 8);
    for (int i = 0; i < static_cast<int>(verticesT.size() / 8); ++i) {
        indices.push_back(i);
    }
    // clang-format on

    Mesh cubeMesh = {verticesT, indices};
    ObjectAttribute positionAttr = {3, GL_FLOAT, sizeof(float)};
    ObjectAttribute textureCoordinatesAttr = {2, GL_FLOAT, sizeof(float)};
    ObjectAttribute surfaceNormalAttr = {3, GL_FLOAT, sizeof(float)};

    // Instanced shading attr
    ObjectAttribute vertexShadingAttr = {1, GL_FLOAT, sizeof(float)};

    // Instanced Model Matrix
    ObjectAttribute matAttr1 = {4, GL_FLOAT, sizeof(glm::vec4)};
    ObjectAttribute matAttr2 = {4, GL_FLOAT, sizeof(glm::vec4)};
    ObjectAttribute matAttr3 = {4, GL_FLOAT, sizeof(glm::vec4)};
    ObjectAttribute matAttr4 = {4, GL_FLOAT, sizeof(glm::vec4)};

    this->mesh = cubeMesh;
    this->attributes = {
        positionAttr,
        textureCoordinatesAttr,
        surfaceNormalAttr,
        vertexShadingAttr,
        matAttr1,
        matAttr2,
        matAttr3,
        matAttr4};
    this->position = position;
    this->texturePath = _texturePath;
}

void Cube::ApplyShadingMap(VertexShadingMap &sm, glm::vec3 position) {
    // Pattern: when a neighbour is 1 below, shade the bottom corners of the side face facing it.
    //          when a neighbour is 1 above, shade the top face's edge corners closest to it.
    int dy = 0;

    // +X neighbour
    dy = position.y - Settings::yTransform(Settings::calculateNoise(position.x + 1, position.z));
    if (dy == 1) // 1 below -> shade +position.x face bottom (vertices 6, 7)
    {
        sm[{6, Face::PosX}] = 1;
        sm[{7, Face::PosX}] = 1;
    } else if (dy == -1) // 1 above -> shade +Y face's +position.x edge (vertices 2, 3)
    {
        sm[{2, Face::PosY}] = 1;
        sm[{3, Face::PosY}] = 1;
    }

    // -position.x neighbour
    dy = position.y - Settings::yTransform(Settings::calculateNoise(position.x - 1, position.z));
    if (dy == 1) // shade -position.x face bottom (vertices 4, 5)
    {
        sm[{4, Face::NegX}] = 1;
        sm[{5, Face::NegX}] = 1;
    } else if (dy == -1) // shade +Y face's -position.x edge (vertices 0, 1)
    {
        sm[{0, Face::PosY}] = 1;
        sm[{1, Face::PosY}] = 1;
    }

    // +position.zneighbour
    dy = position.y - Settings::yTransform(Settings::calculateNoise(position.x, position.z + 1));
    if (dy == 1) // shade +position.zface bottom (vertices 4, 7)
    {
        sm[{4, Face::PosZ}] = 1;
        sm[{7, Face::PosZ}] = 1;
    } else if (dy == -1) // shade +Y face's +position.zedge (vertices 0, 3)
    {
        sm[{0, Face::PosY}] = 1;
        sm[{3, Face::PosY}] = 1;
    }

    // -position.zneighbour
    dy = position.y - Settings::yTransform(Settings::calculateNoise(position.x, position.z - 1));
    if (dy == 1) // shade -position.zface bottom (vertices 5, 6)
    {
        sm[{5, Face::NegZ}] = 1;
        sm[{6, Face::NegZ}] = 1;
    } else if (dy == -1) // shade +Y face's -position.zedge (vertices 1, 2)
    {
        sm[{1, Face::PosY}] = 1;
        sm[{2, Face::PosY}] = 1;
    }

    // Diagonals: shade a single corner on the top face when the diagonal neighbour is above.

    // +X+position.zdiagonal -> top corner 3
    dy = position.y - Settings::yTransform(Settings::calculateNoise(position.x + 1, position.z + 1));
    if (dy == -1)
        sm[{3, Face::PosY}] = 1;

    // +X-position.zdiagonal -> top corner 2
    dy = position.y - Settings::yTransform(Settings::calculateNoise(position.x + 1, position.z - 1));
    if (dy == -1)
        sm[{2, Face::PosY}] = 1;

    // -X+position.zdiagonal -> top corner 0
    dy = position.y - Settings::yTransform(Settings::calculateNoise(position.x - 1, position.z + 1));
    if (dy == -1)
        sm[{0, Face::PosY}] = 1;

    // -X-position.zdiagonal -> top corner 1
    dy = position.y - Settings::yTransform(Settings::calculateNoise(position.x - 1, position.z - 1));
    if (dy == -1)
        sm[{1, Face::PosY}] = 1;
}