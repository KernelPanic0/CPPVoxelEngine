#include "Scene.hpp"

Scene::Scene(World world_) : pWorld(std::make_unique<World>(world_)), pCamera(std::make_shared<Camera>(Camera()))
{
    // glfwSetWindowUserPointer(window->window, camera.get());
}

void Scene::RenderFrame()
{
    // needs to be done faster
    for (Object obj : pWorld->GetChunkObjectsForCameraPosition(pCamera->cameraPos.x, pCamera->cameraPos.z))
    {
        AddSceneObject(obj);
    }

    graphicsManager->RenderObjects(objectList);
}