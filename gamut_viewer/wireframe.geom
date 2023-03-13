#version 320 es

//in VertexToGeom {
//
//} vertexToGeom[];

out lowp vec3 gf_barycentricCoords;

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;
void main() {
    gf_barycentricCoords = vec3(1., 0., 0.);
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gf_barycentricCoords = vec3(0., 1., 0.);
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gf_barycentricCoords = vec3(0., 0., 1.);
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}
