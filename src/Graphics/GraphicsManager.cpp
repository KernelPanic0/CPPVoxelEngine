#include "GraphicsManager.hpp"

// GraphicsManager::GraphicsManager(Shader shaderProgram)
// {
//     this->shaderProgram = shaderProgram;
//     shaderProgram.use();
// }

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
    SceneObject newSceneObject = {object, vao.id, vbo.id, ebo.id};

    return newSceneObject;
}

void GraphicsManager::RenderObjects(std::vector<SceneObject> objectList) // TEMPORARY TEST
{
    // glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    // glm::mat4 projection = glm::mat4(1.0f);
    // projection = glm::perspective(glm::radians(65.0f), (float)800 / (float)600, 0.1f, 1000.0f);

    // const float radius = 10.0f;
    // view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // // pass transformation matrices to the shader
    // shader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    // shader->setMat4("view", view);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->setVec3("aPos", glm::vec3(0, 0, 0));
    shader->setVec3("aColor", glm::vec3(0, 0, 0));

    // glm::mat4 model = glm::mat4(1.0f);
    // int yTransform = 1;

    // for (int i = 0; i < objectList.size(); i++)
    // {
    //     Object thisObject = objectList[i].object;
    //     model = glm::translate(model, glm::vec3(thisObject.x, thisObject.y, thisObject.z));
    //     shader->setMat4("model", model);
    // }
    // glClearColor(0.5843f, 0.7922f, 0.9882f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window->window);
}