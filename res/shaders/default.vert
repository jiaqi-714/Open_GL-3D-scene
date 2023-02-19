#version 330 core

uniform mat4 p;
uniform mat4 v;
uniform mat4 m;

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texco;

out vec3 v_pos;
out vec3 v_normal;
out vec2 v_texco;

// out vec4 p_pos;

void main(void) {
    mat4 mv = v * m;
    vec4 view_pos = mv * vec4(a_pos, 1);

    // mat4 mvp = p * v * m;
    // vec4 p_pos = mvp * vec4(a_pos, 1);

    v_pos = view_pos.xyz;
    v_normal = mat3(mv) * a_normal;
    v_texco = a_texco;

    gl_Position = p * view_pos;
}