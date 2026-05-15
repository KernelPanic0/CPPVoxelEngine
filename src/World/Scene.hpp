#pragma once
#include "World.hpp"
#include "../Camera/Camera.hpp"
#include "../Graphics/GraphicsManager.hpp"
#include "../GLFW/Input.hpp"
#include <memory>

class Scene
{
    std::vector<SceneObject> objectList;
    std::unique_ptr<GraphicsManager> graphicsManager;
    std::shared_ptr<Camera> camera;

public:
    Scene(World world);
    void Render();
    void AddSceneObject(const Object &object);
};