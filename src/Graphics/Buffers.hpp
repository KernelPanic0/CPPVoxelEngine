#pragma once

#include "../includes/glad/glad.h"
#include "./GLFW/Window.hpp"
#include <GLFW/glfw3.h> // System-installed GLFW
#include "./shader_util.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"
#include <vector>

class VertexArray
{
public:
    GLuint id;
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void Unbind() const;
    void AddAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *offset);
};

class VertexBuffer
{
public:
    GLuint id;
    VertexBuffer(GLfloat *vertices, GLsizeiptr size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
};

class ElementBuffer
{
public:
    GLuint id;
    ElementBuffer(GLuint *indices, GLsizeiptr size);
    ~ElementBuffer();
    void Bind() const;
    void Unbind() const;
};