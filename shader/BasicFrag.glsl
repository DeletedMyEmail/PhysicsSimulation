#version 330 core

out vec4 f_color;

in vec4 v_color;

float near = 0.1f;
float far = 1000.0f;
float LinearizeDepth(float depth);

void main() {
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    f_color = v_color;
}

float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}