#pragma once
#include <vector>
#include "../includes/glad/glad.h"
#include "Buffers.hpp"
#include "../World/Objects/Object.hpp"
#include "memory"
#include "../GLFW/Window.hpp"

struct SceneObject
{
    Object object;
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<ElementBuffer> ebo;
};

class GraphicsManager
{
private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Window> window;

public:
    // GraphicsManager(Shader shaderProgram);
    GraphicsManager();
    ~GraphicsManager();
    SceneObject CreateSceneObject(Object object);
    void RenderObjects(const std::vector<SceneObject> &objectList); // TEMPORARY TEST
};