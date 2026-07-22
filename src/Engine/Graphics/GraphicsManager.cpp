#include "GraphicsManager.hpp"
GraphicsManager::GraphicsManager() : fbo(FrameBuffer(800, 400)), tbo(TextureBuffer()) {
    shader = std::make_unique<Shader>("./src/Engine/Graphics/Shaders/shader_instanced.vert",
                                      "./src/Engine/Graphics/Shaders/shader.frag");
    lightShader = std::make_unique<Shader>(
        "./src/Engine/Graphics/Shaders/shader_water.vert",
        "./src/Engine/Graphics/Shaders/shader_water.frag");

    shader->use();
    // shader->setVec3("objectColor", 1.0f, 1.0f, 0.0f);
    shader->setVec3("lightColor", 1.0, 0.733, 0.529);
    shader->setVec3("lightPos", 10, 20, 10);
    glEnable(GL_DEPTH_TEST);

    // Face culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

GraphicsManager::~GraphicsManager() {
    shader.reset();
}

Renderable GraphicsManager::CreateRenderable(const Object &object) {
    std::shared_ptr<VertexArray> vao =
        std::make_shared<VertexArray>(); // Objects with the same mesh and
                                         // layout (attributes/foormat) should
                                         // share a VAO for optimal performance.
                                         // This needs to be changed.
    std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(object.mesh.vertices.data(), object.mesh.vertices.size() * 4);
    std::shared_ptr<VertexBuffer> instanceVbo = std::make_shared<VertexBuffer>(nullptr, 0);
    std::shared_ptr<ElementBuffer> ebo = std::make_shared<ElementBuffer>((GLuint *)object.mesh.indices.data(), object.mesh.indices.size() * 4);
    vbo->Bind();

    // calculate stride
    GLsizei stride = 0;
    for (int i = 0; i < 3; i++) {
        stride += object.attributes[i].size * object.attributes[i].typeSize;
    }

    // calculate offset
    GLsizeiptr offset = 0;

    // insert all regular attributes
    for (int i = 0; i < 3; i++) {
        glVertexAttribPointer(i,
                              object.attributes[i].size,
                              object.attributes[i].type,
                              GL_FALSE,
                              stride,
                              (const GLvoid *)offset);

        offset += object.attributes[i].size * object.attributes[i].typeSize;
        glEnableVertexAttribArray(i);
    }

    // insert instanced attributes
    instanceVbo->Bind();

    for (int i = 0; i < 4; i++) {
        glVertexAttribPointer(3 + i,
                              4,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(glm::mat4),
                              (const GLvoid *)(i * sizeof(glm::vec4))); // offset per column
        glEnableVertexAttribArray(3 + i);
        glVertexAttribDivisor(3 + i, 1);
    }

    // generate texture (if any)
    unsigned int textureId = 0;
    if (object.texturePath != "") {
        auto cachedTexture = textureCache.find(object.texturePath);

        if (cachedTexture != textureCache.end()) {
            textureId = cachedTexture->second;
        } else {
            textureId = GenerateTexture(object.texturePath);
            textureCache.insert({object.texturePath, textureId});
        }
    }

    Renderable newRenderable = {object, std::move(vao), std::move(vbo), std::move(instanceVbo), std::move(ebo), textureId};
    return newRenderable;
}

void GraphicsManager::ClearRenderCache() {
    objectsToRender.clear();
    instanceCounts.clear();
}

void GraphicsManager::AddObjectsForRendering(const std::vector<RawObject> &objects) {
    objectsToRender = objects;
    instanceCounts.clear();

    std::unordered_map<int, std::vector<glm::mat4>> groupedModelMatrices;
    for (const auto &obj : objectsToRender) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(obj.position));
        groupedModelMatrices[obj.id].push_back(model);

        for (float shade : obj.shadingData) {
            aoData.push_back(shade);
        }
    }

    for (auto &[id, matrices] : groupedModelMatrices) {
        auto renderableIt = objectMap.find(id);
        if (renderableIt == objectMap.end()) {
            continue;
        }

        tbo.Buffer(aoData.data(), aoData.size() * sizeof(float));

        renderableIt->second.instanceVbo->Bind();
        renderableIt->second.instanceVbo->Buffer(glm::value_ptr(matrices[0]), static_cast<GLsizeiptr>(matrices.size() * sizeof(glm::mat4)));
        instanceCounts[id] = static_cast<GLsizei>(matrices.size());
    }
}

void GraphicsManager::AddRenderable(int rawObjectId, const Object &object) {
    Renderable newRenderable = CreateRenderable(object);

    objectMap[rawObjectId] = newRenderable;
}

void GraphicsManager::RenderObjects(
    const std::pair<glm::mat4, glm::mat4> viewProjection, glm::vec3 cameraPos,
    Window &window, UI &userInterface) {
    glClearColor(0.09f, 0.09f, 0.43f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    shader->setMat4("projection", viewProjection.second);
    shader->setMat4("view", viewProjection.first);
    shader->setVec3("camPos", cameraPos);
    shader->setInt("aoData", 1);

    for (auto const &[id, renderableObj] : objectMap) {
        auto countIt = instanceCounts.find(id);
        if (countIt == instanceCounts.end() || countIt->second == 0) {
            continue;
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderableObj.textureId);

        tbo.Bind();

        renderableObj.vao->Bind();
        renderableObj.vbo->Bind();
        renderableObj.ebo->Bind();
        glDrawArraysInstanced(GL_TRIANGLES, 0, renderableObj.object.mesh.indices.size(), countIt->second);
        // glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(renderableObj.object.mesh.indices.size()), GL_UNSIGNED_INT, (const void *)0, countIt->second);
    }

    // render model viewer thingy, currently broken
    fbo.Bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    objectMap[0].vao->Bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, objectMap[0].textureId);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, 0, 0));

    shader->use();
    lightShader->setMat4("projection", glm::perspective(glm::radians(45.0f), (float)4 / 3, 0.1f, 1000.0f));
    lightShader->setMat4("view", glm::lookAt(glm::vec3(sin(glfwGetTime()) * 3, 1.5, cos(glfwGetTime()) * 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
    shader->setMat4("model", model);

    objectMap[0].ebo->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(objectMap[0].object.mesh.indices.size()), GL_UNSIGNED_INT, (const void *)0);
    fbo.Unbind();
    userInterface.Render((ImTextureID)(intptr_t)fbo.textureId);

    // render everything
    glfwSwapBuffers(window.window);
}

unsigned int GraphicsManager::GenerateTexture(std::string path) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *textureData =
        stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    unsigned int textureToGen;
    glGenTextures(1, &textureToGen);

    glBindTexture(GL_TEXTURE_2D, textureToGen);
    // set wrapping / filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // This might need to be optimised later as not all textures need to be
    // RGBA.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    // temporary disabled because of edge-bleeding bug
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);

    return textureToGen;
}