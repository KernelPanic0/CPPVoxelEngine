#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TextureCoord;
in vec3 FragWorldPos;

uniform sampler2D objectTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragWorldPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec4 result = vec4((ambient + diffuse), 1.0) * texture(objectTexture, TextureCoord);
    FragColor = result;
}
