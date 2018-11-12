#version 410

layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec2 VertexTexCoord;

out vec2 TexCoord;

void main ()
{
    TexCoord = VertexTexCoord;
    gl_Position = vec4(VertexPosition, 1.0);
}
