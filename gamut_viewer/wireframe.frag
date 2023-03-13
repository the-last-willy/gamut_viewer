#version 320 es

#define float lowp float

in lowp vec3 gf_barycentricCoords;

out lowp vec4 f_color;

void main() {
    float m = min(min(gf_barycentricCoords.x, gf_barycentricCoords.y), gf_barycentricCoords.z);
    f_color = vec4(mix(vec3(1.), vec3(0.2), smoothstep(0.05, 0.08, m)), 1.);
}
