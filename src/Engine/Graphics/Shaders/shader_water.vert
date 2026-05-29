#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

out vec3 Normal;
out vec2 TextureCoord;
out vec3 FragWorldPos;

void main()
{
    vec3 pos = aPos;
    pos.x += sin(time + pos.y) * 0.05;
    pos.z += sin(time + pos.x) * 0.05;
    pos.y += cos(time + pos.z) * 0.05;

    gl_Position = projection * view * model * vec4(pos, 1.0);
    FragWorldPos = vec3(model * vec4(pos, 1.0));
    Normal = aNormal;
}