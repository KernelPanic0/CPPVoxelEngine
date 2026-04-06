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
    GLuint vao, vbo, ebo;
};

class GraphicsManager
{
private:
    GLuint currentlyBoundVAO;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Window> window;
    // Need a list of scene objects to then be able to able to bind to them and render them
    // std::vector<SceneObject> objectList;

public:
    // GraphicsManager(Shader shaderProgram);
    GraphicsManager();
    ~GraphicsManager();
    SceneObject CreateSceneObject(Object object);
    void RenderObjects(std::vector<SceneObject> objectList);
};