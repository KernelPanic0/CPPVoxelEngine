#include "GraphicsManager.hpp"

GraphicsManager::GraphicsManager()
{
    window = std::make_unique<Window>();

    shader = std::make_unique<Shader>("./src/Graphics/Shaders/test_shader2.vert", "./src/Graphics/Shaders/test_shader2.frag");
    shader->use();
    glEnable(GL_DEPTH_TEST);
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
        offset += object.attributes[i].size * object.attributes[i].typeSize; // FIX: use typeSize, not type enum value
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::mat4(1.0f); // init identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);

        GLint m_viewport[4];
        glGetIntegerv(GL_VIEWPORT, m_viewport);

        projection = glm::perspective(glm::radians(45.0f), (float)m_viewport[2] / (float)m_viewport[3], 0.1f, 1000.0f);

        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        view = glm::lookAt(glm::vec3(camX, 0, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0, 0, -5));

        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36); // vertex count needs to be made dynamic
        glfwSwapBuffers(window->window);
    }
}