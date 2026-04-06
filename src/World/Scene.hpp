#pragma once
#include "../Camera/Camera.hpp"
#include "../Graphics/GraphicsManager.hpp"
#include <memory>

class Scene
{
    std::vector<SceneObject> objectList;
    std::unique_ptr<GraphicsManager> graphicsManager;
    Camera camera;

public:
    Scene();
    void Render();
    void AddSceneObject(const Object &object);
};