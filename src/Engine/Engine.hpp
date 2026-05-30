#include "../Camera/Camera.hpp"
#include "Graphics/GraphicsManager.hpp"
#include "../World/World.hpp"
#include "./Scene.hpp"
#include "../GLFW/Input.hpp"

class Engine
{
private:
    std::unique_ptr<Scene> pScene;
    std::shared_ptr<Window> pWindow;
    std::shared_ptr<GraphicsManager> pGraphicsManager;
    std::shared_ptr<Camera> pCamera;

public:
    Engine();
    void RenderFrame();
    void MainLoop();
};