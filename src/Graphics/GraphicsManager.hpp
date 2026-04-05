#include <vector>
#include "../includes/glad/glad.h"
#include "Buffers.hpp"
#include "../World/Objects/Object.hpp"

struct SceneObject
{
    Object object;
    GLuint vao, vbo, ebo;
};

class GraphicsManager
{
private:
    GLuint currentlyBoundVAO;
    std::vector<GLuint> ids;
    // Need a list of scene objects to then be able to able to bind to them and render them
    std::vector<SceneObject> objectList;

public:
    GraphicsManager();
    ~GraphicsManager();
    void AddSceneObject(Object object);
    void DrawAllObjects();
};