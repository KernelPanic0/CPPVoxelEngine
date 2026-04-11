#pragma once
#include <GLFW/glfw3.h> // System-installed GLFW
#include "../includes/imgui/imgui.h"
#include "Camera/Camera.hpp"
#include "misc/Settings.hpp"

namespace Input
{
    void MouseCallback(GLFWwindow *window, double xpos, double ypos);
    void ProcessInput(GLFWwindow *window, bool &showUi);
    extern float lastX, lastY;
}