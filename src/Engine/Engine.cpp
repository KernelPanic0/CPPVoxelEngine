#include "Engine.hpp"

Engine::Engine() : pWindow(std::make_shared<Window>()), pGraphicsManager(std::make_unique<GraphicsManager>()), pScene(std::make_unique<Scene>(Scene(World()))), UserInterface(std::make_unique<UI>(pWindow))
{
    glfwSetWindowUserPointer(pWindow->window, pScene->GetCamera());
}

void Engine::RenderFrame()
{
    pGraphicsManager->ClearRenderCache();

    // needs to be done faster
    for (Object obj : pScene->GetObjectsForRendering())
    {
        pGraphicsManager->AddRenderable(obj);
    }

    pGraphicsManager->RenderObjects(pScene->GetViewProjection(), pScene->GetCamera()->cameraPos, *pWindow.get(), *UserInterface.get()); // not good, but function needs to use window, not own it
}

void Engine::MainLoop()
{
    while (!glfwWindowShouldClose(pWindow->window))
    {
        Input::ProcessInput(pWindow->window, Settings::uiVisible);
        // really this shouldn't be in "Settings".
        Settings::updateDeltaTime();

        // render
        RenderFrame();
    }
}