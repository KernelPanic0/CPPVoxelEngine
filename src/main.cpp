#include "World/Scene.hpp"
#include "World/Objects/Cube.hpp"
#include "GLFW/Window.hpp"

int main()
{
    Scene scene;

    // std::vector<float> vertices = {
    //     0.5f, 0.5f, 0.0f,   // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f   // top left
    // };

    // std::vector<int> indices = {
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };

    // Mesh triangleM = {vertices, indices};
    // ObjectAttribute position = {3, GL_FLOAT, sizeof(float)};

    // Object triangle(triangleM, {position}, glm::vec3(0, 0, 0));

    Cube c(glm::vec3(0, 0, 0));

    scene.AddSceneObject(c);
    scene.Render();
}