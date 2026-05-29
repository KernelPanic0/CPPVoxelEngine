#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TextureCoord;
in vec3 FragWorldPos;
in vec3 Pos;
in float ShadeLevel;

uniform sampler2D objectTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragWorldPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    float fogMaxDist = 120.0;
    float fogMinDist = 0.1;
    vec4 fogColor = vec4(0.4, 0.4, 0.4, 1.0);

    float dist = length(FragWorldPos.xyz - camPos);
    float fogFactor = (fogMaxDist - dist) / (fogMaxDist - fogMinDist);
    fogFactor = clamp(fogFactor, 0.05, 1.0);

    vec4 result = texture(objectTexture, TextureCoord) * ((vec4(-ShadeLevel * 0.7, -ShadeLevel * 0.7, -ShadeLevel * 0.7, 1.0) + 1.0));
    FragColor = mix(fogColor, result, fogFactor);
}