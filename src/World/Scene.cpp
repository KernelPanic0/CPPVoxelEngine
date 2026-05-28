#include "Scene.hpp"
#include <thread>

Scene::Scene(World world_) : world(std::make_unique<World>(world_))
{
    this->camera = std::make_shared<Camera>();
    this->graphicsManager = std::make_unique<GraphicsManager>(camera);
}

void Scene::AddSceneObject(const Object &object)
{
    for (const SceneObject &obj : objectList)
    {
        if (obj.object.position == object.position)
            return;
    }

    SceneObject newSceneObject = graphicsManager->CreateSceneObject(object);
    objectList.push_back(std::move(newSceneObject));
}

void Scene::Render()
{
    GLFWwindow *window = graphicsManager->GetWindow();
    while (!glfwWindowShouldClose(window))
    {
        // needs to be done faster
        for (Object obj : world->GetChunkObjectsForCameraPosition(camera->cameraPos.x, camera->cameraPos.z))
        {
            AddSceneObject(obj);
        }

        Input::ProcessInput(graphicsManager->GetWindow(), Settings::uiVisible);
        // really this shouldn't be in "Settings".
        Settings::updateDeltaTime();

        graphicsManager->RenderObjects(objectList);
    }
}