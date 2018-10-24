#version 410

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 TexCoord;

out vec2 TextureCoord;

void main()
{
    TextureCoord = TexCoord;
    gl_Position = vec4(VertexPosition, 1.0);
}
