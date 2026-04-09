#include "Object.hpp"

Object::Object() : position(glm::vec3(0, 0, 0)) {};
Object::Object(Mesh mesh, std::vector<ObjectAttribute> attributes, glm::vec3 position) : mesh(mesh), attributes(attributes), position(position) {};