#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec4 a_color;

out vec4 v_color;
out vec3 v_normal;

uniform mat4 u_modelViewProj;

void main() {
    v_color = a_color;
    v_normal = a_normal;
    gl_Position = u_modelViewProj * vec4(a_position, 1.0);
}