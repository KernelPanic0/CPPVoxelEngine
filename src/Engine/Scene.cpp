#include "Scene.hpp"

Scene::Scene(World world_) : pWorld(std::make_unique<World>(world_)), pCamera(std::make_shared<Camera>(Camera()))
{
    // glfwSetWindowUserPointer(window->window, camera.get());
}

std::vector<Object> Scene::GetObjectsForRendering()
{
    return pWorld->GetChunkObjectsForCameraPosition(pCamera->cameraPos.x, pCamera->cameraPos.z);
}