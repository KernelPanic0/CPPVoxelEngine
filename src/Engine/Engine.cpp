#include "Engine.hpp"

Engine::Engine() : pScene(std::make_unique<Scene>(Scene(World()))), pWindow(std::make_shared<Window>()), pGraphicsManager(std::make_unique<GraphicsManager>(pCamera)) {}

void Engine::RenderFrame()
{
    // pScene->RenderFrame();

    // belongs in scene
    // needs to be done faster
    for (Object obj : pWorld->GetChunkObjectsForCameraPosition(pCamera->cameraPos.x, pCamera->cameraPos.z))
    {
        AddRenderable(obj);
    }

    Input::ProcessInput(graphicsManager->GetWindow(), Settings::uiVisible);
    // really this shouldn't be in "Settings".
    Settings::updateDeltaTime();

    graphicsManager->RenderObjects(objectList);
}

void Engine::AddRenderable(std::vector<Renderable> &objectList, const Object &object)
{
    std::erase_if(objectList, [&](const Renderable &so)
                  { return glm::length(pCamera->cameraPos) - glm::length(so.object.position) > 10; });

    for (const Renderable &obj : objectList)
    {
        if (obj.object.position == object.position)
            return;
    }

    Renderable newRenderable = pGraphicsManager->CreateRenderable(object);
    objectList.push_back(std::move(newRenderable));
}

void Engine::MainLoop()
{
    while (!glfwWindowShouldClose(pWindow->window))
    {
        Input::ProcessInput(pWindow->window, Settings::uiVisible);
        // really this shouldn't be in "Settings".
        Settings::updateDeltaTime();

        // render
    }
}