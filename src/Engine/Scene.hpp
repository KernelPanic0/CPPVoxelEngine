#pragma once
#include "../GLFW/Input.hpp"
#include "../World/World.hpp"
#include <algorithm>
#include <memory>

class Scene {
  private:
    std::shared_ptr<Camera> pCamera;
    std::unique_ptr<World> pWorld;
    std::pair<int, int> lastChunks = {99, 99}; // used to prevent repeated expensive object fetching from world
    std::vector<Object> cachedWorldObjects;

  public:
    bool sceneDirty = true;
    Scene(World world);
    std::vector<Object> GetObjectsForRendering();
    std::pair<glm::mat4, glm::mat4> GetViewProjection();
    Camera *GetCamera(); // temporary
};