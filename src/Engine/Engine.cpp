#include "Engine.hpp"

Engine::Engine() : pWindow(std::make_shared<Window>()), pGraphicsManager(std::make_unique<GraphicsManager>()), pScene(std::make_unique<Scene>(Scene(World()))), UserInterface(std::make_unique<UI>(pWindow)) {
    glfwSetWindowUserPointer(pWindow->window, pScene->GetCamera());

    for (auto obj : pScene->GetObjectMapping()) {
        pGraphicsManager->AddRenderable(obj.first, obj.second);
    }
}

void Engine::RenderFrame() {
    if (pScene->sceneDirty) {
        pGraphicsManager->ClearRenderCache();

        pGraphicsManager->AddObjectsForRendering(pScene->GetObjectsForRendering());

        pScene->sceneDirty = false;
    }
    pGraphicsManager->RenderObjects(pScene->GetViewProjection(), pScene->GetCamera()->cameraPos, *pWindow.get(), *UserInterface.get()); // not good, but function needs to use window, not own it // needs to be done faster
}

void Engine::MainLoop() {
    while (!glfwWindowShouldClose(pWindow->window)) {
        Input::ProcessInput(pWindow->window, Settings::uiVisible);
        // really this shouldn't be in "Settings".
        Settings::updateDeltaTime();

        // render
        RenderFrame();
    }
}
