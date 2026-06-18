#pragma once
#include "../../../includes/glad/glad.h"
#include "../../GLFW/Window.hpp"
#include "../../UI/UI.hpp"
#include "../../World/Objects/Object.hpp"
#include "../../misc/stb_image.h"
#include "Buffers.hpp"
#include "memory"
#include <unordered_map>
#include <vector>

struct Renderable {
    Object object;
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<ElementBuffer> ebo;
    unsigned int textureId;
};

class GraphicsManager {
  private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> lightShader;
    std::unordered_map<std::string, int> textureCache; // prevents reloading already loaded textures

    unsigned int GenerateTexture(std::string path);
    Renderable CreateRenderable(Object object);
    FrameBuffer fbo;

  public:
    std::vector<Renderable> objectRenderCache;

    GraphicsManager();
    ~GraphicsManager();
    void ClearRenderCache();
    void AddRenderable(const Object &object);
    void RenderObjects(const std::pair<glm::mat4, glm::mat4> viewProjection, glm::vec3 cameraPosition, Window &window, UI userInterface);
};
