# === Makefile for voxel project ===

CXX := g++
CXXFLAGS := -std=c++20 -O2 -I./includes -I./includes/imgui -I./src/
LDFLAGS := -lglfw -lGL -ldl -lX11 -lpthread -lXrandr -lXi
TARGET := voxel

SRC := ./src/main.cpp \
    ./includes/glad/glad.c \
    ./src/stb_image.cpp \
    ./src/GLFW/Init.cpp \
    ./src/Camera/Camera.cpp \
    ./src/Input/Input.cpp \
    ./includes/imgui/imgui.cpp \
    ./includes/imgui/imgui_draw.cpp \
    ./includes/imgui/imgui_demo.cpp \
    ./includes/imgui/imgui_tables.cpp \
    ./includes/imgui/imgui_widgets.cpp \
    ./includes/imgui/imgui_impl_glfw.cpp \
    ./includes/imgui/imgui_impl_opengl3.cpp

OBJ := $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
