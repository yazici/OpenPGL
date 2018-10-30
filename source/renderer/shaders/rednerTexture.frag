#version 410

in vec2 TextureCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
//    FragColor = vec4(texture(ourTexture, TextureCoord).r);
    
    FragColor = vec4(1.0);
}
