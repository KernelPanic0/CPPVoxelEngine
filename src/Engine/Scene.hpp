#pragma once
#include "../World/World.hpp"
#include <algorithm>
#include <memory>
#include "./Graphics/GraphicsManager.hpp"

class Scene
{
private:
    std::vector<SceneObject> objectList;
    std::unique_ptr<GraphicsManager> graphicsManager;
    std::shared_ptr<Camera> pCamera;
    std::unique_ptr<World> pWorld;

public:
    Scene(World world);
    void RenderFrame();
};