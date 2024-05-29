#version 330 core

in vec4 v_color;
in vec3 v_normal;

out vec4 f_color;

void main() {
    vec3 lightColor = vec3(0.5, 0.5, 0.5);
    vec3 lightPos = vec3(0.0, -15.0, -10.0);

    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * v_color.rgb;

    // diffuse
    vec3 norm = normalize(v_normal);
    vec3 toLight = normalize(v_normal-lightPos);
    vec3 diffuse = vec3(v_color) * clamp(dot(norm, toLight), 0.0, 1.0);

    vec3 resColor = ambient + diffuse;
    f_color = vec4(resColor, v_color.a);
}

/*
float LinearizeDepth(float depth) {
    float near = 0.1f;
    float far = 1000.0f;
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}*/