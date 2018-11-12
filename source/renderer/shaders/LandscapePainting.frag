#version 410

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

uniform float height[10];
uniform vec3 colors[10];

float convert(float val, float f1, float f2, float t1, float t2)
{
    return (val - f1) / (f2-f1) * (t2-t1) + t1;
}

void main ()
{    
    int i = 0, j = 0;
    float h = texture(ourTexture, TexCoord).r;
    
    for (i = 0; i < 10; i++) {
        if (h <= height[i]) {
            break;
        }
    }
    
    j = (i == 9 ? i : i + 1);
    
    float res = convert(h, height[i], height[j], 0.0, 1.0);
    vec3 c = (i == j ? vec3(colors[i]) : mix(colors[i], colors[j], res));
    
    FragColor = vec4(c, 1.0);
}

