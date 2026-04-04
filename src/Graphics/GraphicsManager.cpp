#include "GraphicsManager.hpp"

GraphicsManager::GraphicsManager()
{
}

void GraphicsManager::AddSceneObject(Mesh mesh)
{
    VertexArray vao;
    VertexBuffer vbo(mesh.vertices.data());
    ElementBuffer ebo(mesh.indices.data());

    vao.Unbind();
    SceneObject newObject = {mesh, vao.id, vbo.id, ebo.id};

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // grassTexture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    objectList.push_back(newObject);
}

void GraphicsManager::DrawAllMeshes()
{
}