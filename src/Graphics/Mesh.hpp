#pragma once

#include "../includes/glad/glad.h"
#include "./GLFW/Window.hpp"
#include <GLFW/glfw3.h> // System-installed GLFW
#include "./shader_util.h"

#include "Input/Input.hpp"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "./VertexManager.hpp"

// debugging data
// struct MeshStats
// {
//     static int meshCount;
//     static int drawCallsCount;
// };

struct Mesh
{
    std::vector<float> vertices;
    std::vector<int> indices;
};