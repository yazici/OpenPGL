#version 410 core

in vec3 position;
in vec3 normal;
in vec3 lightPosition;

uniform vec3 uIntensity;
uniform vec3 uKa;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

out vec4 fragColor;

vec3 AmbientDiffuseSpecular(vec3 lightPosition, vec3 normal)
{
    vec3 toLight = normalize(lightPosition - position);
    vec3 toEye = normalize(-position);

    // ambient
    vec3 ambient = uKa;

    // diffuse
    float d = max(dot(toLight, normal), 0.0f);
    vec3 diffuse = uKd * d;

    // specular
    vec3 halfWay = normalize(toEye + toLight);
    float s = pow(max(dot(halfWay, normal), 0.0f), uShininess); 
    vec3 specular = uKs * s;

    return uIntensity * (ambient + diffuse + specular);
}

void main()
{
    vec3 color = AmbientDiffuseSpecular(lightPosition, normal);
    fragColor = vec4(color, 1.0f);
}
