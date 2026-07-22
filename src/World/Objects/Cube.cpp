#include "Cube.hpp"

Cube::Cube(glm::vec3 position, std::string _texturePath) {
    // Texture is a 4:3 cross unfolding (4 cells wide x 3 cells tall)
    // y is 0 or 1/3 for bottom face, 1/3 or 2/3 for side faces, 2/3 or 1 for top face
    constexpr float sLo = 1.0f / 3.0f;
    constexpr float sHi = 2.0f / 3.0f;
    constexpr float bCtr = 1.0f / 6.0f;
    constexpr float tCtr = 5.0f / 6.0f;

    // clang-format off
    std::vector<float> verticesT = {
        // Position           // Texture        // Normal (might need later..?)

        // -Z (back) face
         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.5f,   sLo,      0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f, -0.5f,  0.5f,   sLo,      0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.5f,   sHi,      0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,

        -0.5f,  0.5f, -0.5f,  0.5f,   sHi,      0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.25f,  sHi,      0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,

         0.5f,  0.5f, -0.5f,  0.25f,  sHi,      0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -0.5f,  0.375f, 0.5f,     0.0f,  0.0f, -1.0f,

        // +Z (front) face
        -0.5f, -0.5f,  0.5f,  0.5f,   sLo,      0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.25f,  sLo,      0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,

         0.5f, -0.5f,  0.5f,  0.25f,  sLo,      0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.25f,  sHi,      0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,

         0.5f,  0.5f,  0.5f,  0.25f,  sHi,      0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.5f,   sHi,      0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f,  0.5f,   sHi,      0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.5f,   sLo,      0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  0.5f,  0.375f, 0.5f,     0.0f,  0.0f,  1.0f,

        // -X (left) face
        -0.5f,  0.5f,  0.5f,  0.25f,  sHi,     -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.5f,   sHi,     -1.0f,  0.0f,  0.0f,
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.5f,   sHi,     -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.5f,   sLo,     -1.0f,  0.0f,  0.0f,
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.5f,   sLo,     -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.25f,  sLo,     -1.0f,  0.0f,  0.0f,
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.25f,  sLo,     -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.25f,  sHi,     -1.0f,  0.0f,  0.0f,
        -0.5f,  0.0f,  0.0f,  0.375f, 0.5f,    -1.0f,  0.0f,  0.0f,

        // +X (right) face
         0.5f,  0.5f,  0.5f,  0.5f,   sHi,      1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.5f,   sLo,      1.0f,  0.0f,  0.0f,
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,

         0.5f, -0.5f,  0.5f,  0.5f,   sLo,      1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      1.0f,  0.0f,  0.0f,
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,

         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.25f,  sHi,      1.0f,  0.0f,  0.0f,
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,

         0.5f,  0.5f, -0.5f,  0.25f,  sHi,      1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.5f,   sHi,      1.0f,  0.0f,  0.0f,
         0.5f,  0.0f,  0.0f,  0.375f, 0.5f,     1.0f,  0.0f,  0.0f,

        // -Y (bottom) face
        -0.5f, -0.5f, -0.5f,  0.25f,  0.0f,     0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      0.0f, -1.0f,  0.0f,
         0.0f, -0.5f,  0.0f,  0.375f, bCtr,     0.0f, -1.0f,  0.0f,

         0.5f, -0.5f, -0.5f,  0.25f,  sLo,      0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.5f,   sLo,      0.0f, -1.0f,  0.0f,
         0.0f, -0.5f,  0.0f,  0.375f, bCtr,     0.0f, -1.0f,  0.0f,

         0.5f, -0.5f,  0.5f,  0.5f,   sLo,      0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.5f,   0.0f,     0.0f, -1.0f,  0.0f,
         0.0f, -0.5f,  0.0f,  0.375f, bCtr,     0.0f, -1.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.5f,   0.0f,     0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.25f,  0.0f,     0.0f, -1.0f,  0.0f,
         0.0f, -0.5f,  0.0f,  0.375f, bCtr,     0.0f, -1.0f,  0.0f,

        // +Y (top) face
         0.5f,  0.5f, -0.5f,  0.25f,  1.0f,     0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.25f,  sHi,      0.0f,  1.0f,  0.0f,
         0.0f,  0.5f,  0.0f,  0.375f, tCtr,     0.0f,  1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.25f,  sHi,      0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.5f,   sHi,      0.0f,  1.0f,  0.0f,
         0.0f,  0.5f,  0.0f,  0.375f, tCtr,     0.0f,  1.0f,  0.0f,

        -0.5f,  0.5f,  0.5f,  0.5f,   sHi,      0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.5f,   1.0f,     0.0f,  1.0f,  0.0f,
         0.0f,  0.5f,  0.0f,  0.375f, tCtr,     0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  0.5f,   1.0f,     0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.25f,  1.0f,     0.0f,  1.0f,  0.0f,
         0.0f,  0.5f,  0.0f,  0.375f, tCtr,     0.0f,  1.0f,  0.0f,
    };

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

std::vector<float> Cube::ShadingMapToFlatArray(const VertexShadingMap &sm) {
    std::vector<float> result(72, 0.0f);

    // 1. Populate all outer corner vertices
    for (int i = 0; i < 72; i++) {
        if (vertexDescs[i].corner == -1)
            continue;

        auto it = sm.find({vertexDescs[i].corner, vertexDescs[i].face});
        result[i] = (it != sm.end()) ? static_cast<float>(it->second) : 0.0f;
    }

    // 2. Calculate center vertex values for each face (6 faces x 12 vertices)
    for (int faceIdx = 0; faceIdx < 6; faceIdx++) {
        int base = faceIdx * 12;

        float cornerSum = 0.0f;
        for (int i = 0; i < 12; i++) {
            int idx = base + i;
            if (vertexDescs[idx].corner != -1) {
                cornerSum += result[idx];
            }
        }

        // Each face contains 4 corners, with each corner appearing twice across the 12 vertices.
        // Summing the 8 corner vertices and dividing by 8 gives the exact 4-corner average.
        float centerShade = cornerSum / 8.0f;

        for (int i = 0; i < 12; i++) {
            int idx = base + i;
            if (vertexDescs[idx].corner == -1) {
                result[idx] = centerShade;
            }
        }
    }

    return result;
}