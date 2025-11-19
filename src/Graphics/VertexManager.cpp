#include "VertexManager.hpp"

VertexArray::VertexArray() { // Create a new VBO, bind to it and insert data into it
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() const {
    glBindVertexArray(id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::addAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

VertexBuffer::VertexBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) { // Create a new VBO, bind to it and insert data into it
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ElementBuffer::ElementBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) { 
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &id);
}

void ElementBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}