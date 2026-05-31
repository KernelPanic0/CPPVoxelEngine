#include "UI.hpp"

UI::UI(const std::shared_ptr<Window> &window)
{
    this->pWindow = window;
    // Camera *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window->window));
    // this->camera = camera;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    ImGui_ImplGlfw_InitForOpenGL(window->window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
}

void UI::Render(ImTextureID texture)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (Settings::uiVisible)
    {
        ImGui::BeginTabBar("Hi");
        if (ImGui::BeginTabItem("Info"))
        {
            ImGui::Text("Hello this is a test %d", 123);
            ImGui::Text("Camera position: ");

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Model Viewer"))
        {
            ImGui::Text("Hi");
            ImGui::Image(texture, ImVec2(320, 240), ImVec2(0, 1), ImVec2(1, 0));

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();

        // // std::cout << camera->cameraPos.x << "\n";
        // ImGui::Text("x: %f", camera->cameraPos.x);
        // ImGui::Text("y: %f", camera->cameraPos.y);
        // ImGui::Text("z: %f", camera->cameraPos.z);
        // ImGui::ShowDemoWindow(&Settings::uiVisible);
    }

    // ImGui rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(pWindow->window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}