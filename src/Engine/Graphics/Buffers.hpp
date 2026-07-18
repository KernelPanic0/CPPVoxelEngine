#pragma once

#include "../../../includes/glad/glad.h"
#include "../../../includes/glm/glm.hpp"
#include "../../../includes/glm/gtc/matrix_transform.hpp"
#include "../../../includes/glm/gtc/type_ptr.hpp"
#include "../../GLFW/Window.hpp"
#include "../../misc/shader_util.h"
#include <GLFW/glfw3.h> // System-installed GLFW
#include <vector>

class VertexArray {
  public:
    GLuint id;
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void Unbind() const;
    void AddAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *offset);
};

class VertexBuffer {
  public:
    GLuint id;
    VertexBuffer(const GLfloat *vertices, GLsizeiptr size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
    void Buffer(float *vertices, GLsizeiptr size) const;
};

class ElementBuffer {
  public:
    GLuint id;
    ElementBuffer(GLuint *indices, GLsizeiptr size);
    ~ElementBuffer();
    void Bind() const;
    void Unbind() const;
};

class FrameBuffer {
  public:
    GLuint id;
    GLuint textureId;
    FrameBuffer(int width, int height);
    void Bind() const;
    void Unbind() const;
    ~FrameBuffer();
};

class TextureBuffer {
  public:
    GLuint tboId;
    GLuint textureId;
    TextureBuffer(GLfloat *data, GLsizeiptr size);
    void Bind() const;
    void Unbind() const;
    ~TextureBuffer();
};
