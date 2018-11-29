#version 410

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    FragColor = vec4(texture(tex, TexCoord).r);
}
