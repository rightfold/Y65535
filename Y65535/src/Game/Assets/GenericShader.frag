#version 420
#extension GL_ARB_explicit_uniform_location : require

in vec3 fragmentPosition;
in vec3 computedVertexNormal;

layout(location = 2) uniform vec3 lightPosition;

out vec4 color;

void main() {
    vec3 ambient = vec3(0.3f, 0.3f, 0.3f);
    vec3 vertexColor = vec3(0.8f, 0.5f, 0.9f);

    vec3 lightDirection = normalize(lightPosition - fragmentPosition);
    float diffuse = max(dot(computedVertexNormal, lightDirection), 0.0f);

    vec3 light = ambient + vec3(diffuse);
    color = vec4(light * vertexColor, 1.0f);
}
