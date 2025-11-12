#include "./stb_image.h"
#include <random>
#include <unordered_map>
#include "./misc/Settings.hpp"
#include "./Camera/Camera.hpp"

// glm / math
#include "../includes/imgui/imconfig.h"
#include "../includes/imgui/imgui_impl_glfw.h"
#include "../includes/imgui/imgui_impl_opengl3.h"
#include "../includes/imgui/imgui.h"

#include "../includes/glad/glad.h"
#include "./GLFW/Init.hpp"
#include <GLFW/glfw3.h>  // System-installed GLFW
#include "./shader_util.h"

#include "Input/Input.hpp"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#if defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)
    // Windows-specific includes/code
    #include "imconfig.h"
    #include "imgui_impl_glfw.h"
    #include "imgui_impl_opengl3.h"
    #include "imgui.h"

    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
    #include "shader_util.h"
    #include "stb_image.h"
    #include <random>
    #include <unordered_map>

    // glm / math
    #include "glm/glm.hpp"
    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>
#endif

// imgui
#include "../includes/imgui/imconfig.h"

#include <cmath>
#include "../includes/PerlinNoise.hpp"

#include <iostream>
#include <time.h>
void drawChunk(const siv::PerlinNoise perlin, Shader ourShader, int chunkX, int chunkY, unsigned int snowTextureId, unsigned int grassTextureId);

#define CHUNK_SIZE 16

float lastFrame = 0.0f; // Time of last frame
// float lastX = 400, lastY = 300; // Mouse pos

// float yaw, pitch;

unsigned int fps = 0;
float lastCalculated = 1.0f;



int main()
{
    GLFWwindow* window = Window().Init();
    Camera camera({0.0f, 0.0f, 3.0f});

    glfwSetWindowUserPointer(window, &camera);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330"); // Use your shader version
    ImGui::StyleColorsDark();

    // ImGUI State
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // glfwSetCursorPosCallback(window, mouse_callback); // Problematic function for ImGui not capturing mouse input
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------

    Shader shaderProgram("./src/shader.vert", "./src/shader.frag"); // you can name your shader files however you like

    // set up vertex grassTextureData (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
     // Sides
    -0.5f, -0.5f, -0.5f,  0.5f, 0.25f, // 1 bottom right
     0.5f, -0.5f, -0.5f,  0.25f, 0.25f, // 1 bottom left
     0.5f,  0.5f, -0.5f,  0.25f, 0.75f, // 1 top left
     0.5f,  0.5f, -0.5f,  0.25f, 0.75f, // 2 top left
    -0.5f,  0.5f, -0.5f,  0.5f, 0.75f, // 2 top right
    -0.5f, -0.5f, -0.5f,  0.5f, 0.25f, // 2 bottom right

    -0.5f, -0.5f,  0.5f,  0.5f, 0.25f, 
     0.5f, -0.5f,  0.5f,  0.25f, 0.25f,
     0.5f,  0.5f,  0.5f,  0.25f, 0.75f,
     0.5f,  0.5f,  0.5f,  0.25f, 0.75f,
    -0.5f,  0.5f,  0.5f,  0.5f, 0.75f, 
    -0.5f, -0.5f,  0.5f,  0.5f, 0.25f, 

    -0.5f,  0.5f,  0.5f,  0.25f, 0.75f,  // 1 top right (1 top left)
    -0.5f,  0.5f, -0.5f,  0.5f, 0.75f, // 1 bottom right (1 top right)
    -0.5f, -0.5f, -0.5f,  0.5f, 0.25f, // 1 bottom left (1 bottom right)
    -0.5f, -0.5f, -0.5f,  0.5f, 0.25f, // 2 bottom left (2 bottom right)
    -0.5f, -0.5f,  0.5f,  0.25f, 0.25f, // 2 top left (2 bottom left)
    -0.5f,  0.5f,  0.5f,  0.25f, 0.75f, // 2 top right (1 top left)

     0.5f,  0.5f,  0.5f,  0.5f,  0.75f,
     0.5f,  0.5f, -0.5f,  0.25f, 0.75f, 
     0.5f, -0.5f, -0.5f,  0.25f, 0.25f, 
     0.5f, -0.5f, -0.5f,  0.25f, 0.25f, 
     0.5f, -0.5f,  0.5f,  0.5f,  0.25f,
     0.5f,  0.5f,  0.5f,  0.5f,  0.75f,
    // Bottom
    -0.5f, -0.5f, -0.5f,  0.25f, 0.0f, // 1 bottom left
     0.5f, -0.5f, -0.5f,  0.25f, 0.25f, // 1 top left
     0.5f, -0.5f,  0.5f,  0.5f, 0.25f, // 1 top right 
     0.5f, -0.5f,  0.5f,  0.5f, 0.25f, // 2 top right 
    -0.5f, -0.5f,  0.5f,  0.5f, 0.0f, // 2 bottom right
    -0.5f, -0.5f, -0.5f,  0.25f, 0.0f, // bottom left
    // Top
    -0.5f,  0.5f, -0.5f,  0.25f, 0.75, // 1 bottom left
     0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // 1 top left
     0.5f,  0.5f,  0.5f,  0.5f, 1.0f, // 1 top right
     0.5f,  0.5f,  0.5f,  0.5f, 1.0f, // 2 top right
    -0.5f,  0.5f,  0.5f,  0.5f, 0.75f, // 2 bottom right
    -0.5f,  0.5f, -0.5f,  0.25f, 0.75, // 2 bottom left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };


    std::random_device rd;
    const siv::PerlinNoise::seed_type seed = rd();

    // std::cout << seed << std::endl;

	const siv::PerlinNoise perlin{ seed };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // grassTexture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* grassTextureData = stbi_load("./assets/grass.jpg", &width, &height, &nrChannels, 0);
    unsigned char* snowTextureData = stbi_load("./assets/snow.png", &width, &height, &nrChannels, 0);


    unsigned int grassTexture, snowTexture;
    glGenTextures(1, &grassTexture);
    glGenTextures(1, &snowTexture);


    glBindTexture(GL_TEXTURE_2D, grassTexture);
    // set wrapping / filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grassTextureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, snowTexture);
    // set wrapping / filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, snowTextureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(grassTextureData);
    stbi_image_free(snowTextureData);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(camera.cameraPos - cameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // render loop
    glEnable(GL_DEPTH_TEST);
    // -----------
    int xChunks = 15, zChunks = 15;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        // ImGui

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        Input::processInput(window, &show_demo_window);

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // ImGui rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 
        // input
        // -----

        float currentFrame = glfwGetTime();
        Settings::deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (currentFrame - lastCalculated >= 1.0f) {
            lastCalculated = currentFrame;
           std::string str = (std::string)"CPP Voxel Engine FPS: " + std::to_string(fps);

            glfwSetWindowTitle(window, str.c_str());
            fps = 0;
        }
        else {
            fps++;
        }

        // get viewport properties
        GLint m_viewport[4];

        glGetIntegerv(GL_VIEWPORT, m_viewport);

        Settings::SCR_WIDTH = m_viewport[2]; 
        Settings::SCR_HEIGHT = m_viewport[3];

        // render
        // ------
        glClearColor(0.5843f, 0.7922f, 0.9882f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // bind textures on corresponding grassTexture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, grassTexture);

        // activate shader
        shaderProgram.use();

        // create transformations
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(65.0f), (float)Settings::SCR_WIDTH / (float)Settings::SCR_HEIGHT, 0.1f, 1000.0f);

        const float radius = 10.0f;
        float camX = sin(glfwGetTime() / 5) * radius;
        float camZ = cos(glfwGetTime() / 5) * radius;
        view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);

        // pass transformation matrices to the shader
        shaderProgram.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        shaderProgram.setMat4("view", view);

        // render ubes
        double noise;
        glBindVertexArray(VAO);

        // Draw Chunks
        int currentChunkX = static_cast<int>(std::floor(camera.cameraPos.x / CHUNK_SIZE));
        int currentChunkZ = static_cast<int>(std::floor(camera.cameraPos.z / CHUNK_SIZE));

        const int renderDistance = 10; // chunks in each direction

        for (int dx = -renderDistance; dx <= renderDistance; dx++) {
            for (int dz = -renderDistance; dz <= renderDistance; dz++) {
                int chunkX = currentChunkX + dx;
                int chunkZ = currentChunkZ + dz;

                drawChunk(perlin, shaderProgram, chunkX, chunkZ, snowTexture, grassTexture);
            }
        }
        //std::cout << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// Maybe in the future optimize all these calculations with caching (unordered map ?) 
// These params for grass and snow texture are currently awful but I will fix it 

void drawChunk(const siv::PerlinNoise perlin, Shader ourShader, int chunkX, int chunkZ, unsigned int snowTextureId, unsigned int grassTextureId) {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            double noise = perlin.octave2D_01(((x+CHUNK_SIZE*chunkX) * 0.01), ((z+CHUNK_SIZE*chunkZ) * 0.01), 4);
            int yTransform = (int)-2.0f * noise * 30;

            model = glm::translate(model, glm::vec3((float)(x+CHUNK_SIZE*chunkX), yTransform, (float)(z+CHUNK_SIZE*chunkZ)));
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // Fix holes in terrain 
            double nextNoiseX = perlin.octave2D_01(((x + 1 + CHUNK_SIZE * chunkX) * 0.01), ((z + CHUNK_SIZE * chunkZ) * 0.01), 4); // still y
            double nextNoiseZ = perlin.octave2D_01(((x + CHUNK_SIZE * chunkX) * 0.01), ((z + 1 + CHUNK_SIZE * chunkZ) * 0.01), 4); // still y 

            if (std::abs(nextNoiseX - yTransform) > 1) {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3((float)(x + CHUNK_SIZE * chunkX), yTransform+1, (float)(z + CHUNK_SIZE * chunkZ)));
                ourShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            else if (std::abs(nextNoiseX - yTransform) > 1) {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3((float)(x + CHUNK_SIZE * chunkX), yTransform + 1, (float)(z + CHUNK_SIZE * chunkZ)));
                ourShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------