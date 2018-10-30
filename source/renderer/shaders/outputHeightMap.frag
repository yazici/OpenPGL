#version 410

in vec2 TextureCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

uniform vec3 Colors[10];
uniform vec3 Heights[10];

void main()
{
    
    vec4 colorA;
    vec4 colorB;
    int i = 0;
    
    for (i = 0; i < 10; i++) {
        if (texture(ourTexture, TextureCoord).r < Heights[i]) {
            break;
        }
    }
    
    colorA = Colors[i];
    
    if (i == 0) {
        colorB = Colors[i + 1];
    } else {
        colorB = Colors[i - 1];
    }
    
    FragColor = vec4(mix(colorA, colorB, texture(ourTexture, TextureCoord).r));
}
