#version 410 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VERTEX {
    vec3 normal;
} vertex[];

uniform float uNormalLength;

void normalLine(int i)
{
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
    gl_Position = gl_in[i].gl_Position + vec4(vertex[i].normal, 0.0f) * uNormalLength;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    normalLine(0);
    normalLine(1);
    normalLine(2);
}
