#pragma once
#include <vector>
#include "../includes/glad/glad.h"
#include "Buffers.hpp"
#include "../World/Objects/Object.hpp"
#include "memory"
#include "../GLFW/Window.hpp"
#include "../misc/stb_image.h"

struct SceneObject
{
    Object object;
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<ElementBuffer> ebo;
    unsigned int textureId;
};

class GraphicsManager
{
private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Window> window;

    unsigned int GenerateTexture(std::string path);

public:
    // GraphicsManager(Shader shaderProgram);
    GraphicsManager();
    ~GraphicsManager();
    SceneObject CreateSceneObject(Object object);
    void RenderObjects(const std::vector<SceneObject> &objectList); // TEMPORARY TEST
};