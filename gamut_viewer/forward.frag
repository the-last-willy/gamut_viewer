#version 320 es

in lowp vec3 vf_color;

layout (location = 0) out lowp vec4 f_color;

void main() {
    f_color = vec4(vf_color, 1.);
}
