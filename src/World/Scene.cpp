#include "Scene.hpp"

Scene::Scene()
{
    this->graphicsManager = std::make_unique<GraphicsManager>();
    this->camera = std::make_shared<Camera>();

    ImGui::CreateContext();
    // this passes in the raw pointer. Bypasses the shared/unique pointer of Camera. This may need to be changed at some point.
    glfwSetWindowUserPointer(graphicsManager->GetWindow(), camera.get());
}

void Scene::AddSceneObject(const Object &object)
{
    SceneObject newSceneObject = graphicsManager->CreateSceneObject(object);
    objectList.push_back(std::move(newSceneObject));
}

void Scene::Render()
{
    bool temp = false;

    GLFWwindow *window = graphicsManager->GetWindow();
    while (!glfwWindowShouldClose(window))
    {
        // sometimes there is a bug where you can only move the camera view up and down.
        Input::ProcessInput(graphicsManager->GetWindow(), temp);
        // really this shouldn't be in "Settings".
        Settings::updateDeltaTime();
        // camera->
        graphicsManager->RenderObjects(objectList);
    }
}