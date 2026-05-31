#pragma once
#include "../includes/imgui/imgui.h"
#include "../includes/imgui/imgui_impl_glfw.h"
#include "../includes/imgui/imgui_impl_opengl3.h"
#include "../GLFW/Window.hpp"
#include <memory>

class UI
{
private:
    bool visible = true;
    std::shared_ptr<Window> pWindow;
    Camera *camera;

public:
    UI(const std::shared_ptr<Window> &window);
    void Render(ImTextureID texture);
};