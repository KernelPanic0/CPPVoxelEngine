#include "../../Graphics/Mesh.hpp"

struct Object
{
    Mesh mesh;
    std::vector<ObjectAttribute> attributes;
};

struct ObjectAttribute
{
    unsigned int size;
    GLenum type;
    unsigned int typeSize;
};