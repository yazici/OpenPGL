#version 410 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

out VERTEX {
    vec3 normal;
} vertex;

uniform mat4 uMVP;
uniform mat4 uProjection;
uniform mat3 uNormal;

void main()
{
    vec4 pos = vec4(vertexPosition, 1.0f);
    vec3 n = vec3(uProjection * vec4(uNormal * vertexNormal, 0.0f));
    gl_Position = uMVP * pos;
    vertex.normal = normalize(n);
}
