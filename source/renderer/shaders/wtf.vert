#version 410

layout (location = 0) in vec3 position;

uniform mat4 uMVP;
uniform vec3 uColor;
out vec3 color;

void main()
{
    color = uColor;
    gl_Position =  uMVP * vec4(position, 1.0);
}

