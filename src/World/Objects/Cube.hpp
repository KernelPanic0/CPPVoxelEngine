#pragma once
#include "../../Graphics/Mesh.hpp"
#include "Object.hpp"

class Cube : public Object
{
public:
    Cube(glm::vec3 position, std::string texturePath = "");
};
