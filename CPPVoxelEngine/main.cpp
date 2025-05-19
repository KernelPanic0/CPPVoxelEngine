#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_util.h"
#include "stb_image.h"
#include <random>
#include <unordered_map>
// glm
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PerlinNoise.hpp"
#include <iostream>

#include <time.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void drawChunks(const siv::PerlinNoise perlin, Shader ourShader, int chunkX, int chunkY);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

#define CHUNK_SIZE 16

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = 400, lastY = 300; // Mouse pos

float yaw, pitch;

unsigned int fps = 0;
float lastCalculated = 1.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since z-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CPP Voxel Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------

    Shader shaderProgram("shader.vert", "shader.frag"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
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

    std::cout << seed << std::endl;

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
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("./grass.jpg", &width, &height, &nrChannels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    // set wrapping / filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    // render loop
    glEnable(GL_DEPTH_TEST);
    // -----------
    int xChunks = 15, zChunks = 15;

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);


        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
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

        SCR_WIDTH = m_viewport[2]; 
        SCR_HEIGHT = m_viewport[3];


        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // activate shader
        shaderProgram.use();

        // create transformations
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(65.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

        const float radius = 10.0f;
        float camX = sin(glfwGetTime() / 5) * radius;
        float camZ = cos(glfwGetTime() / 5) * radius;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // pass transformation matrices to the shader
        shaderProgram.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        shaderProgram.setMat4("view", view);

        // render ubes
        double noise;
        glBindVertexArray(VAO);

        // Draw Chunks
        if (cameraPos.x / xChunks >= (CHUNK_SIZE - 5)) {
            xChunks += 5;
        }
        else if (cameraPos.z / zChunks >= (CHUNK_SIZE - 5)) {
            zChunks += 5;
        }
        for (unsigned int x = 1; x < xChunks; x++) {
            for (unsigned int z = 1; z < zChunks; z++) {
                drawChunks(perlin, shaderProgram, x, z);
            }
        }
        std::cout << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
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
void drawChunks(const siv::PerlinNoise perlin, Shader ourShader, int chunkX, int chunkZ) {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            double noise = perlin.octave2D_01(((x+CHUNK_SIZE*chunkX) * 0.01), ((z+CHUNK_SIZE*chunkZ) * 0.01), 4);
            int yTransform = (int)-2.0f * noise * 30;
            model = glm::translate(model, glm::vec3((float)(x+CHUNK_SIZE*chunkX), yTransform, (float)(z+CHUNK_SIZE*chunkZ)));
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


        const float cameraSpeed = 15.05f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}