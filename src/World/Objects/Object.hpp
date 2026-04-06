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
    int x, y, z;
    Mesh mesh;
    std::vector<ObjectAttribute> attributes;
    Object(Mesh mesh, std::vector<ObjectAttribute> attributes, int x, int y, int z);
    Object();
};