#include "Scene.hpp"

Scene::Scene(World world_) : pWorld(std::make_unique<World>(world_)), pCamera(std::make_shared<Camera>(Camera())) {}

std::vector<RawObject> Scene::GetObjectsForRendering() {
    auto [currentChunkX, currentChunkZ] = pWorld->GetChunkCoordinatesFromCameraPosition(pCamera->cameraPos.x, pCamera->cameraPos.z);

    if (lastChunks.first != currentChunkX || lastChunks.second != currentChunkZ) {
        cachedWorldObjects = pWorld->GetChunkObjectsForCameraPosition(pCamera->cameraPos.x, pCamera->cameraPos.z);
        lastChunks = {currentChunkX, currentChunkZ};
        sceneDirty = true;
        return cachedWorldObjects;
    } else {
        return cachedWorldObjects;
    }
}

std::pair<glm::mat4, glm::mat4> Scene::GetViewProjection() {
    return std::pair(pCamera->GetView(), pCamera->GetProjection());
}

Camera *Scene::GetCamera() // temporary
{
    return pCamera.get();
}

std::unordered_map<int, Object> Scene::GetObjectMapping() {
    return pWorld->GetObjectMapping();
}