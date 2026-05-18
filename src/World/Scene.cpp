#include "Scene.hpp"

Scene::Scene(World world) : world(std::make_unique<World>(world))
{
    this->camera = std::make_shared<Camera>();
    this->graphicsManager = std::make_unique<GraphicsManager>(camera);

    for (Object obj : world.GetObjects())
    {
        AddSceneObject(obj);
    }
}

void Scene::AddSceneObject(const Object &object)
{
    SceneObject newSceneObject = graphicsManager->CreateSceneObject(object);
    objectList.push_back(std::move(newSceneObject));
}

void Scene::Render()
{
    GLFWwindow *window = graphicsManager->GetWindow();
    while (!glfwWindowShouldClose(window))
    {
        objectList.clear();
        for (Object obj : world->GetChunksForCameraPosition(camera->cameraPos.x, camera->cameraPos.z).objects)
        {
            AddSceneObject(obj);
        }

        Input::ProcessInput(graphicsManager->GetWindow(), Settings::uiVisible);
        // really this shouldn't be in "Settings".
        Settings::updateDeltaTime();
        graphicsManager->RenderObjects(objectList);
    }
}