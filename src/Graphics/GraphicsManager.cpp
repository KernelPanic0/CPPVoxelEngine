#include "GraphicsManager.hpp"
#include "numeric"

GraphicsManager::GraphicsManager()
{
}

void GraphicsManager::AddSceneObject(Object object)
{
    VertexArray vao;
    VertexBuffer vbo(object.mesh.vertices.data());
    ElementBuffer ebo(object.mesh.indices.data());

    vbo.Bind();
    // insert all attributes
    // calculate stride
    GLsizei stride = 0;
    for (const auto &attr : object.attributes)
    {
        stride += attr.size * attr.typeSize;
    }

    for (int i = 0; i < object.attributes.size(); i++)
    {
        glVertexAttribPointer(i, object.attributes[i].size, object.attributes[i].type, GL_FALSE, stride, (void *)0);
        glEnableVertexAttribArray(i);
    }

    vao.Unbind();
    SceneObject newObject = {object, vao.id, vbo.id, ebo.id};

    objectList.push_back(newObject);
}

void GraphicsManager::DrawAllObjects()
{
}