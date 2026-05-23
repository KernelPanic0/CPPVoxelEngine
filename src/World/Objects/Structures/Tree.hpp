#pragma once
#include "../Cube.hpp"

class Tree
{
public:
    std::vector<Cube> objects;

    Tree(glm::vec3 position);
};