#include "Scene.hpp"

Scene::Scene(World world_) : pWorld(std::make_unique<World>(world_)), pCamera(std::make_shared<Camera>(Camera()))
{
}

std::vector<Object> Scene::GetObjectsForRendering()
{
    return pWorld->GetChunkObjectsForCameraPosition(pCamera->cameraPos.x, pCamera->cameraPos.z);
}

std::pair<glm::mat4, glm::mat4> Scene::GetViewProjection()
{
    return std::pair(pCamera->GetView(), pCamera->GetProjection());
}

Camera *Scene::GetCamera() // temporary
{
    return pCamera.get();
}