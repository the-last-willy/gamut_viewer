#version 320 es

layout (location = 0) uniform mat4 u_MVP;

layout (location = 0) in vec3 v_vertex;

void main() {
    gl_Position = u_MVP * vec4(v_vertex, 1.);
}
