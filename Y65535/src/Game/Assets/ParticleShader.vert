#version 420
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec3 vertexPosition;

layout(location = 0) uniform mat4 m;
layout(location = 1) uniform mat4 vp;

void main() {
    gl_Position = vp * m * vec4(vertexPosition, 1.0f);
}
