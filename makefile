CXX := g++
CXXFLAGS := -std=c++20 -O2 -I./includes -I./includes/imgui -I./src/ -g
LDFLAGS := -lglfw -lGL -ldl -lX11 -lpthread -lXrandr -lXi
BUILD_DIR := ./build
TARGET := $(BUILD_DIR)/voxel

SRC := ./src/main.cpp \
    ./includes/glad/glad.c \
    ./src/misc/stb_image.cpp \
    ./src/shader_util.cpp \
    ./src/GLFW/Window.cpp \
    ./src/Camera/Camera.cpp \
    ./src/GLFW/Input.cpp \
    ./src/Graphics/GraphicsManager.cpp \
    ./src/Graphics/Buffers.cpp \
    ./src/Graphics/Mesh.cpp \
    ./src/World/Scene.cpp \
    ./src/World/Objects/Object.cpp \
    ./src/World/Objects/Cube.cpp \
    ./includes/imgui/imgui.cpp \
    ./includes/imgui/imgui_draw.cpp \
    ./includes/imgui/imgui_demo.cpp \
    ./includes/imgui/imgui_tables.cpp \
    ./includes/imgui/imgui_widgets.cpp \
    ./includes/imgui/imgui_impl_glfw.cpp \
    ./includes/imgui/imgui_impl_opengl3.cpp

OBJ := $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)
OBJ := $(patsubst %,$(BUILD_DIR)/%,$(OBJ))

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: all
	./$(TARGET)

.PHONY: all clean run