#include "UI.hpp"

UI::UI(std::shared_ptr<Window> &window)
{
    this->window = window;
    IMGUI_CHECKVERSION();
    ImGuiContext *ctx = ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    ImGui_ImplGlfw_InitForOpenGL(window->window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
}

void UI::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // if (visible)
    ImGui::ShowDemoWindow(&visible);

    // ImGui rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window->window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}