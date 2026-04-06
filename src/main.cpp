#include "World/Scene.hpp"
#include "World/Objects/Cube.hpp"
#include "GLFW/Window.hpp"

int main()
{
    Scene scene;
    Cube testCube(1, 1, 1);
    Cube testCube2(1, 1, 2);
    GraphicsManager graphicsManager;

    scene.AddSceneObject(testCube);
    scene.AddSceneObject(testCube2);
    while (true)
    {
        scene.Render();
    }
}