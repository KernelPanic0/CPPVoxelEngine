#include "Engine.hpp"

Engine::Engine() : pWindow(std::make_shared<Window>()), pGraphicsManager(std::make_unique<GraphicsManager>()), pScene(std::make_unique<Scene>(Scene(World()))), UserInterface(std::make_unique<UI>(pWindow)) {
  glfwSetWindowUserPointer(pWindow->window, pScene->GetCamera());
}

void Engine::RenderFrame() {
  auto objects = pScene->GetObjectsForRendering();

  std::vector<Object> reconstructedObjects;
  for (Renderable &ro : pGraphicsManager->objectRenderCache) {
    reconstructedObjects.push_back(ro.object);
  }

  if (reconstructedObjects != objects) {
    pGraphicsManager->ClearRenderCache();

    for (Object obj : pScene->GetObjectsForRendering()) {
      pGraphicsManager->AddRenderable(obj);
    }
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
