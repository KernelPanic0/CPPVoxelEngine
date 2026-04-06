#include "Object.hpp"

Object::Object() : x(0), y(0), z(0) {}

Object::Object(Mesh mesh, std::vector<ObjectAttribute> attributes, int x, int y, int z) : mesh(mesh), attributes(attributes), x(x), y(y), z(z) {};