#version 330 core

out vec4 f_color;

in vec4 v_color;
in vec3 v_normal;

float near = 0.1f;
float far = 1000.0f;

float LinearizeDepth(float depth);

void main() {
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightPos = vec3(0.0, 20.0, -32.0);

    // ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(lightPos - gl_FragCoord.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;


    vec3 result = (ambient + diffuse) * v_color.rgb;
    f_color = vec4(result, v_color.a);
}

float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}