#version 410 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

uniform mat4 uModelView;
uniform mat4 uMVP;
uniform mat3 uNormalMatrix;

uniform vec3 uLightPosition;

out vec3 position;
out vec3 normal;
out vec3 lightPosition;

void main()
{
    normal = normalize(uNormalMatrix * vertexNormal);
    position = vec3(uModelView * vec4(vertexPosition, 1.0f));
    lightPosition = vec3(uModelView * vec4(uLightPosition, 1.0f));
    gl_Position = uMVP * vec4(vertexPosition, 1.0f);
}
