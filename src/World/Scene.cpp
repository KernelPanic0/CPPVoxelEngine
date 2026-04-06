#include "Scene.hpp"

Scene::Scene()
{
    this->graphicsManager = std::make_unique<GraphicsManager>();
}

void Scene::AddSceneObject(const Object &object)
{
    SceneObject newSceneObject = graphicsManager->CreateSceneObject(object);
    objectList.push_back(newSceneObject);
}

void Scene::Render()
{
    graphicsManager->RenderObjects(objectList);
}