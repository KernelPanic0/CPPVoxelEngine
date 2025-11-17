#pragma once

#include "../includes/glad/glad.h"
#include "./GLFW/Window.hpp"
#include <GLFW/glfw3.h>  // System-installed GLFW
#include "./shader_util.h"

#include "Input/Input.hpp"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "./VertexManager.hpp"

// debugging data 
struct MeshStats {
    static int meshCount;
    static int drawCallsCount;
};

// this will contain each 
class Mesh {
public:
    VertexArray vao;
    VertexBuffer vbo;
    ElementBuffer ebo;

    GLsizei indexCount;

    
    Mesh(const float vertices[], const int indices[]):
    vbo(vertices, sizeof(vertices)),
    ebo(indices, sizeof(indices)) 
    indexCount(vertices.){
        vao.bind();

        vao.addAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        vao.addAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }

    void draw() const {
        vao.bind();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    }
};