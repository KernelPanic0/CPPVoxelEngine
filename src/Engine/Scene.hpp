#pragma once
#include "../World/World.hpp"
#include <algorithm>
#include <memory>

class Scene
{
private:
    std::shared_ptr<Camera> pCamera;
    std::unique_ptr<World> pWorld;

public:
    Scene(World world);
    std::vector<Object> GetObjectsForRendering();
};