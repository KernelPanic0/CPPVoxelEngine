#include "Cube.hpp"

Cube::Cube(glm::vec3 position, std::string _texturePath)
{
    // clang-format off
    std::vector<float> verticesT = {
        // Position attribute // Texture attribute // Normal attribute
        // Sides
        -0.5f, -0.5f, -0.5f,  0.5f, 0.25f,   0.0f,  0.0f, -1.0f, // 1 bottom right
        0.5f, -0.5f, -0.5f,  0.25f, 0.25f,   0.0f,  0.0f, -1.0f, // 1 bottom left
        0.5f,  0.5f, -0.5f,  0.25f, 0.75f,   0.0f,  0.0f, -1.0f, // 1 top left
        0.5f,  0.5f, -0.5f,  0.25f, 0.75f,   0.0f,  0.0f, -1.0f, // 2 top left
        -0.5f,  0.5f, -0.5f,  0.5f, 0.75f,   0.0f,  0.0f, -1.0f, // 2 top right
        -0.5f, -0.5f, -0.5f,  0.5f, 0.25f,   0.0f,  0.0f, -1.0f, // 2 bottom right

        -0.5f, -0.5f,  0.5f,  0.5f, 0.25f,   0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.25f, 0.25f,   0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.25f, 0.75f,   0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.25f, 0.75f,   0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.5f, 0.75f,   0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.5f, 0.25f,   0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f,  0.25f, 0.75f, -1.0f,  0.0f,  0.0f, // 1 top right (1 top left)
        -0.5f,  0.5f, -0.5f,  0.5f, 0.75f,  -1.0f,  0.0f,  0.0f, // 1 bottom right (1 top right)
        -0.5f, -0.5f, -0.5f,  0.5f, 0.25f,  -1.0f,  0.0f,  0.0f, // 1 bottom left (1 bottom right)
        -0.5f, -0.5f, -0.5f,  0.5f, 0.25f,  -1.0f,  0.0f,  0.0f, // 2 bottom left (2 bottom right)
        -0.5f, -0.5f,  0.5f,  0.25f, 0.25f, -1.0f,  0.0f,  0.0f, // 2 top left (2 bottom left)
        -0.5f,  0.5f,  0.5f,  0.25f, 0.75f, -1.0f,  0.0f,  0.0f, // 2 top right (1 top left)

        0.5f,  0.5f,  0.5f,  0.5f,  0.75f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.25f, 0.75f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.25f, 0.25f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.25f, 0.25f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.5f,  0.25f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.5f,  0.75f,  1.0f,  0.0f,  0.0f,
        // Bottom
        -0.5f, -0.5f, -0.5f,  0.25f, 0.0f,   0.0f, -1.0f,  0.0f, // 1 bottom left
        0.5f, -0.5f, -0.5f,  0.25f, 0.25f,   0.0f, -1.0f,  0.0f, // 1 top left
        0.5f, -0.5f,  0.5f,  0.5f, 0.25f,    0.0f, -1.0f,  0.0f, // 1 top right
        0.5f, -0.5f,  0.5f,  0.5f, 0.25f,    0.0f, -1.0f,  0.0f, // 2 top right
        -0.5f, -0.5f,  0.5f,  0.5f, 0.0f,    0.0f, -1.0f,  0.0f, // 2 bottom right
        -0.5f, -0.5f, -0.5f,  0.25f, 0.0f,   0.0f, -1.0f,  0.0f, // bottom left
        // Top
        -0.5f,  0.5f, -0.5f,  0.25f, 0.75,   0.0f,  1.0f,  0.0f, // 1 bottom left
        0.5f,  0.5f, -0.5f,  0.25f, 1.0f,    0.0f,  1.0f,  0.0f, // 1 top left
        0.5f,  0.5f,  0.5f,  0.5f, 1.0f,     0.0f,  1.0f,  0.0f, // 1 top right
        0.5f,  0.5f,  0.5f,  0.5f, 1.0f,     0.0f,  1.0f,  0.0f, // 2 top right
        -0.5f,  0.5f,  0.5f,  0.5f, 0.75f,   0.0f,  1.0f,  0.0f, // 2 bottom right
        -0.5f,  0.5f, -0.5f,  0.25f, 0.75,   0.0f,  1.0f,  0.0f, // 2 bottom left
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

    this->mesh = cubeMesh;
    this->attributes = {positionAttr, textureCoordinatesAttr, surfaceNormalAttr};
    this->position = position;
    this->texturePath = _texturePath; // Apparently std::strings arent null terminated by default..?
}
