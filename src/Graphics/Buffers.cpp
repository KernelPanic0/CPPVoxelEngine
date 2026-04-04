#include "VertexManager.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
}

void VertexArray::Bind() const
{
    glBindVertexArray(id);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *offset)
{
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

VertexBuffer::VertexBuffer(const void *data)
{ // Create a new VBO, bind to it and insert data into it
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ElementBuffer::ElementBuffer(const void *data)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &id);
}

void ElementBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}