#version 410

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexColor;
layout (location = 2) in vec3 VertexNormalize;

uniform vec4 LightPosition;
uniform vec3 Ld;
uniform vec3 Kd;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;

out vec3 Color;

void main()
{
    vec3 tnorm = normalize(NormalMatrix * VertexNormalize);
    vec4 eyeCoord =  ModelViewMatrix * vec4(VertexPosition, 1.0);
    vec3 s = normalize(vec3(LightPosition - eyeCoord));
    
    Color = Ld * Kd * max(dot(s, tnorm), 0.0f);
    Color = mix(Color, VertexColor, 0.5);
    
    gl_Position = ProjectionMatrix * eyeCoord;
}

