#pragma once
#include <GLFW/glfw3.h>  // System-installed GLFW
#include "../misc/Settings.hpp"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"
#include "Camera/Camera.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
class Window {
public:
    // Sets up callbacks and returns window pointer
    GLFWwindow* Init();
    Window();
    void SetCamera(Camera* camera);
    GLFWwindow* window;
private:
    Camera* camera = nullptr;
};