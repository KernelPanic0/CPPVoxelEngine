#pragma once
#include "../../Graphics/Mesh.hpp"

struct ObjectAttribute
{
    unsigned int size;
    GLenum type;
    unsigned int typeSize;
};

class Object
{
public:
    glm::vec3 position;
    Mesh mesh;
    std::vector<ObjectAttribute> attributes;
    Object(Mesh mesh, std::vector<ObjectAttribute> attributes, glm::vec3 position);
    Object();
};