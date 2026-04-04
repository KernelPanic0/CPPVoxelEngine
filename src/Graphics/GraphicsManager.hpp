#include <vector>
#include "../includes/glad/glad.h"
#include "Mesh.hpp"
#include "VertexManager.hpp"

struct SceneObject
{
    Mesh mesh;
    GLuint vao, vbo, ebo;
    unsigned int attribteCount;
};

class GraphicsManager
{
private:
    GLuint currentlyBoundVAO;
    std::vector<GLuint> ids;
    // Need a list of meshes to then be able to able to bind to them and render them ..?
    std::vector<SceneObject> objectList;

public:
    GraphicsManager();
    ~GraphicsManager();
    void AddSceneObject(Mesh mesh);
    void DrawAllMeshes();
};