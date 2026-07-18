#include "Input.hpp"
#include <iostream>
#include <memory>

namespace Input {
float lastX, lastY = 400.0f;
void MouseCallback(GLFWwindow *window, double xpos, double ypos) {
    ImGuiIO &io = ImGui::GetIO();
    if (io.WantCaptureKeyboard)
        return;

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since z-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    Camera *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));
    camera->MoveCamera(xoffset, yoffset);
}

void ProcessInput(GLFWwindow *window, bool &showUi) {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    Camera *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));
    // Movement
    float cameraSpeed = 30.05f * Settings::deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraSpeed *= 5.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->cameraPos += cameraSpeed * camera->cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->cameraPos -= cameraSpeed * camera->cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->cameraPos -= glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->cameraPos += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * cameraSpeed;

    // Up and down
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera->cameraPos += cameraSpeed * camera->cameraUp;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera->cameraPos += cameraSpeed * -camera->cameraUp;

    static bool lastRightShiftState = false;

    bool currentRightShiftState = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
    if (currentRightShiftState && !lastRightShiftState) {
        showUi = !showUi;
    }
    lastRightShiftState = currentRightShiftState;
    if (showUi == true) {
        ImGui::GetIO().MouseDrawCursor = false;
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange; // Enable Keyboard Controls
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}
} // namespace Input