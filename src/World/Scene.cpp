#include "Scene.hpp"

Scene::Scene(World world)
{
    this->camera = std::make_shared<Camera>();
    // this passes in the raw pointer. Bypasses the shared/unique pointer of Camera. This may need to be changed at some point.

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
        Input::ProcessInput(graphicsManager->GetWindow(), Settings::uiVisible);
        // really this shouldn't be in "Settings".
        Settings::updateDeltaTime();
        graphicsManager->RenderObjects(objectList);
    }
}