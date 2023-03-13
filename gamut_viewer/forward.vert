#version 320 es

layout(location = 0) uniform mat4 u_mvp;

layout (location = 0) in vec3 v_vertex;
layout (location = 1) in vec3 v_color;

out lowp vec3 vf_color;

void main() {
    vec4 csPos = u_mvp * vec4(v_vertex, 1.);

    vf_color = v_color;

    gl_Position = csPos;
}
