#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;

out vec4 v_color;

uniform mat4 u_model;

void main() {
    v_color = vec4(a_color, 1.0);
    gl_Position =  u_model * vec4(a_position, 1.0);
}