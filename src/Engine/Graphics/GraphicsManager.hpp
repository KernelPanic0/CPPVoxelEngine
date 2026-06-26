#pragma once
#include "../../../includes/glad/glad.h"
#include "../../GLFW/Window.hpp"
#include "../../UI/UI.hpp"
#include "../../World/Objects/Object.hpp"
#include "../../World/World.hpp"
#include "../../misc/stb_image.h"
#include "Buffers.hpp"
#include "memory"
#include <unordered_map>
#include <vector>

struct Renderable {
    Object object;
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<VertexBuffer> vbo;
    std::shared_ptr<VertexBuffer> instanceVbo;
    std::shared_ptr<ElementBuffer> ebo;
    unsigned int textureId;
};

class GraphicsManager {
  private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> lightShader;
    std::unordered_map<std::string, int> textureCache; // prevents reloading already loaded textures
    std::unordered_map<int, Renderable> objectMap;     // maps RawObject id to OpenGL Object
    std::unordered_map<int, GLsizei> instanceCounts;   // number of instances per renderable id
    std::vector<RawObject> objectsToRender;

    unsigned int GenerateTexture(std::string path);
    Renderable CreateRenderable(const Object &object);
    FrameBuffer fbo;

  public:
    GraphicsManager();
    ~GraphicsManager();
    void ClearRenderCache();
    void AddRenderable(int rawObjectId, const Object &object);
    void AddObjectsForRendering(const std::vector<RawObject> &objects);
    void RenderObjects(const std::pair<glm::mat4, glm::mat4> viewProjection, glm::vec3 cameraPosition, Window &window, UI &userInterface);
};
