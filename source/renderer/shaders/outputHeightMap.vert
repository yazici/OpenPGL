#version 410

layout (location = 0) in vec3 VertexPosiotion;
layout(location = 2) in vec2 TexCoord;

out vec2 TextureCoord;

void main()
{
    gl_Position = vec4(VertexPosiotion, 1.0);
    TextureCoord = TexCoord;
}
