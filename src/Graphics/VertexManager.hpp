#pragma once

#include "../includes/glad/glad.h"
#include "./GLFW/Window.hpp"
#include <GLFW/glfw3.h>  // System-installed GLFW
#include "./shader_util.h"

#include "Input/Input.hpp"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"
#include <vector>

// class GraphicsManager {
// private:
//     std::vector<GLuint> ids;
// public:
//     void Bind(GLuint id, int type) { glBindBuffer(type, id); }
//     void Unbind(int type) { glBindBuffer(type, 0); }
   
//     void Buffer(const void* data, size_t size, int type) {
//         glBufferData(type, size, data, GL_STATIC_DRAW);
//     }
    
//     GLuint CreateBufferObject() {
//         unsigned int buffer;

//         glGenBuffers(1, &buffer);
//         ids.push_back(buffer);
//         return buffer;
//     } 
// };

class VertexArray {
public:
    GLuint id;

    VertexArray();
    ~VertexArray();
    void bind() const;
    void unbind() const;
    void addAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);
};

class VertexBuffer {
public:
    GLuint id;

    VertexBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};

class ElementBuffer {
public:
    GLuint id;

    ElementBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW); 
    ~ElementBuffer();
    void bind() const;
    void unbind() const;
};