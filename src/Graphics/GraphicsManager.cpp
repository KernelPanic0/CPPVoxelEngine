#include "GraphicsManager.hpp"

GraphicsManager::GraphicsManager()
{
    window = std::make_unique<Window>(); // needs to check if creation did actually happen

    shader = std::make_unique<Shader>("./src/Graphics/Shaders/test_shader.vert", "./src/Graphics/Shaders/test_shader.frag");
    lightShader = std::make_unique<Shader>("./src/Graphics/Shaders/test_shader.vert", "./src/Graphics/Shaders/test_shader_light.frag");

    shader->use();
    // shader->setVec3("objectColor", 1.0f, 1.0f, 0.0f);
    shader->setVec3("lightColor", 1.0, 0.733, 0.529);
    shader->setVec3("lightPos", 10, -20, 10);
    glEnable(GL_DEPTH_TEST);

    // Face culling
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
    // Wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

GraphicsManager::~GraphicsManager()
{
    shader.reset();
    window.reset();
}

SceneObject GraphicsManager::CreateSceneObject(Object object)
{
    std::unique_ptr<VertexArray> vao = std::make_unique<VertexArray>(); // Objects with the same mesh and layout (attributes/foormat) should share a VAO for optimal performance. This needs to be changed.
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

    // generate texture (if any)
    unsigned int textureId = 0;
    if (object.texturePath != "")
    {
        auto cachedTexture = textureCache.find(object.texturePath);

        if (cachedTexture != textureCache.end()) // if texture has already been cached
        {
            textureId = cachedTexture->second;
        }
        else
        {
            textureId = GenerateTexture(object.texturePath);
            textureCache.insert({object.texturePath, textureId});
        }
    }

    SceneObject newSceneObject = {
        object,
        std::move(vao),
        std::move(vbo),
        std::move(ebo),
        textureId};
    return newSceneObject;
}

void GraphicsManager::RenderObjects(const std::vector<SceneObject> &objectList) // TEMPORARY TEST
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const SceneObject &object : objectList)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, object.textureId);

        glm::mat4 view = glm::mat4(1.0f); // init identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);

        GLint m_viewport[4];
        glGetIntegerv(GL_VIEWPORT, m_viewport);

        projection = glm::perspective(glm::radians(45.0f), (float)m_viewport[2] / (float)m_viewport[3], 0.1f, 1000.0f);

        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;

        Camera *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window->window));

        view = glm::lookAt(camera->cameraPos, camera->cameraPos + camera->cameraFront, camera->cameraUp);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(object.object.position));

        if (object.object.position.y == -20) // Is a light. This will be changed
        {
            lightShader->use();
            lightShader->setMat4("projection", projection);
            lightShader->setMat4("view", view);
            lightShader->setMat4("model", model);
        }
        else
        {
            shader->use();
            shader->setMat4("projection", projection);
            shader->setMat4("view", view);
            shader->setMat4("model", model);
        }

        glDrawArrays(GL_TRIANGLES, 0, object.object.mesh.vertices.size());
    }
    glfwSwapBuffers(window->window);
}

unsigned int GraphicsManager::GenerateTexture(std::string path)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *textureData = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    unsigned int textureToGen;
    glGenTextures(1, &textureToGen);

    glBindTexture(GL_TEXTURE_2D, textureToGen);
    // set wrapping / filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureToGen);
    // set wrapping / filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);

    return textureToGen;
}

GLFWwindow *GraphicsManager::GetWindow() const
{
    return window->window; // bad because bypasses unique_ptr
}