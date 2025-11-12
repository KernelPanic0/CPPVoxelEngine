#pragma once
#include <GLFW/glfw3.h>  // System-installed GLFW
#include "../includes/imgui/imgui.h"
#include "Camera/Camera.hpp"
#include "misc/Settings.hpp"

namespace Input {
void mouse_callback(GLFWwindow* window, double xpos, double ypos); 
void processInput(GLFWwindow* window, bool* showUi);
extern float lastX, lastY;
}