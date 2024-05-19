#version 330 core

out vec4 f_color;

in vec4 v_color;

float near = 0.1f;
float far = 1000.0f;

float linearizeDepth(float depth) {
    return (0.5 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float steepness, float offset) {
    float zVal = linearizeDepth(depth);
    return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()  {
    float depth = logisticDepth(gl_FragCoord.z, 0.5f, 0.5f);
    f_color = vec4((1.0f- depth) * vec3(0.85f, 0.85f, 0.90f), v_color.a);
}