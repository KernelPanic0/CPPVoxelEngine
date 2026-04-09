#include "GraphicsManager.hpp"

GraphicsManager::GraphicsManager()
{
    window = std::make_unique<Window>();

    shader = std::make_unique<Shader>("./src/Graphics/Shaders/test_shader.vert", "./src/Graphics/Shaders/test_shader.frag");
    shader->use();
}

GraphicsManager::~GraphicsManager()
{
    shader.reset();
    window.reset();
}

SceneObject GraphicsManager::CreateSceneObject(Object object)
{
    std::unique_ptr<VertexArray> vao = std::make_unique<VertexArray>();
    std::unique_ptr<VertexBuffer> vbo = std::make_unique<VertexBuffer>(object.mesh.vertices.data(), object.mesh.vertices.size() * 4);
    std::unique_ptr<ElementBuffer> ebo = std::make_unique<ElementBuffer>((GLuint *)object.mesh.indices.data(), object.mesh.indices.size() * 4);

    // calculate stride
    GLsizei stride = 0;
    for (const auto &attr : object.attributes)
    {
        stride += attr.size * attr.typeSize;
    }

    // calculate offset
    GLsizeiptr offset = 0;

    // insert all attributes
    for (int i = 0; i < object.attributes.size(); i++)
    {
        glVertexAttribPointer(i, object.attributes[i].size, object.attributes[i].type, GL_FALSE, stride, (const GLvoid *)offset);
        offset += object.attributes[i].size * object.attributes[i].type;
        glEnableVertexAttribArray(i);
    }

    SceneObject newSceneObject = {object, std::move(vao), std::move(vbo), std::move(ebo)};
    return newSceneObject;
}

void GraphicsManager::RenderObjects(const std::vector<SceneObject> &objectList) // TEMPORARY TEST
{
    while (!glfwWindowShouldClose(window->window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window->window);
    }
}