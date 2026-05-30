#include "../Camera/Camera.hpp"
#include "Graphics/GraphicsManager.hpp"
#include "../World/World.hpp"
#include "./Scene.hpp"
#include "../GLFW/Input.hpp"

class Engine
{
private:
    std::shared_ptr<Window> pWindow;
    std::shared_ptr<GraphicsManager> pGraphicsManager;
    std::unique_ptr<Scene> pScene;
    std::unique_ptr<UI> UserInterface;

public:
    Engine();
    void RenderFrame();
    void MainLoop();
};