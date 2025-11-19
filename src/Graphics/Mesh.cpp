#include "Mesh.hpp"

Mesh::Mesh(std::vector<float> vertices, std::vector<int> indices):
vbog(vertices, sizeof(vertices)),
ebo(indices, sizeof(indices)),
indexCount(sizeof(vertices)/sizeof(*vertices)) {
    vao.bind();

    vao.addAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    vao.addAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Mesh::draw() const {
    vao.bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}