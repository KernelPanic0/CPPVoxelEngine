#include "World/Scene.hpp"
#include "GLFW/Window.hpp"

int main()
{
    World w;
    Scene scene(w);

    scene.Render();
}