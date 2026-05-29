#pragma once
#include <vector>
#include "../includes/glad/glad.h"
#include "Buffers.hpp"
#include "../../World/Objects/Object.hpp"
#include "memory"
#include "../../GLFW/Window.hpp"
#include "../../misc/stb_image.h"
#include <unordered_map>
#include <UI/UI.hpp>

struct Renderable
{
    Object object;
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<ElementBuffer> ebo;
    unsigned int textureId;
};

class GraphicsManager
{
private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> lightShader;
    std::unordered_map<std::string, int> textureCache; // prevents reloading already loaded textures
    std::unique_ptr<UI> ui;

    unsigned int GenerateTexture(std::string path);

public:
    GraphicsManager();
    ~GraphicsManager();
    Renderable CreateRenderable(Object object);
    void RenderObjects(const std::vector<Renderable> &objectList);
};