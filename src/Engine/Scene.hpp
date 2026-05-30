#pragma once
#include "../World/World.hpp"
#include <algorithm>
#include "../GLFW/Input.hpp"
#include <memory>

class Scene
{
private:
    std::shared_ptr<Camera> pCamera;
    std::unique_ptr<World> pWorld;

public:
    Scene(World world);
    std::vector<Object> GetObjectsForRendering();
    std::pair<glm::mat4, glm::mat4> GetViewProjection();
    Camera *GetCamera(); // temporary
};