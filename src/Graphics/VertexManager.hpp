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

    VertexArray() { // Create a new VBO, bind to it and insert data into it
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &id);
    }

    void bind() const {
        glBindVertexArray(id);
    }

    void unbind() const {
        glBindVertexArray(0);
    }

    void addAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
        glVertexAttribPointer(index, size, type, normalized, stride, offset);
    }
};

class VertexBuffer {
public:
    GLuint id;

    VertexBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) { // Create a new VBO, bind to it and insert data into it
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }

    ~VertexBuffer() {
        glDeleteBuffers(1, &id);
    }

    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

class ElementBuffer {
public:
    GLuint id;

    ElementBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) { 
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
    }

    ~ElementBuffer() {
        glDeleteBuffers(1, &id);
    }

    void bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};