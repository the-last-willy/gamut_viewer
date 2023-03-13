#pragma once

#include <gamut_viewer/common.hpp>
#include <gamut_viewer/conventions.hpp>

#include <array>
#include <optional>
#include <vector>

#include <glm/glm.hpp>

class TriangleMesh {
public:

    auto indexCount() const -> std::size_t { return indices.size(); }

    auto vertexCount() const -> std::size_t { return vertices.size(); }

    auto hasColors() const -> bool { return !colors.empty(); }

    std::vector<unsigned> indices;
    std::vector<glm::vec3> vertices;

    std::vector<glm::vec3> colors;
};

inline auto cube(int res) {
    auto mesh = TriangleMesh();
    mesh.indices.reserve(res * res * 6);
    mesh.vertices.reserve(res * res * 6);

    auto linearizer = [res](auto i, auto j) {
        return j * res + i;
    };

    for (int f = 0; f < 6; ++f)
        for (int i = 1; i < res; ++i)
            for (int j = 1; j < res; ++j) {
                auto offset = f * res * res;

                mesh.indices.push_back(linearizer(i - 1, j - 1) + offset);
                mesh.indices.push_back(linearizer(i - 1, j - 0) + offset);
                mesh.indices.push_back(linearizer(i - 0, j - 1) + offset);

                mesh.indices.push_back(linearizer(i - 0, j - 1) + offset);
                mesh.indices.push_back(linearizer(i - 1, j - 0) + offset);
                mesh.indices.push_back(linearizer(i - 0, j - 0) + offset);
            }


    // +X.
    for (int i = 0; i < res; ++i)
        for (int j = 0; j < res; ++j) {
            auto x = remap(0.f, float(res - 1), float(i), 0.f, 1.f);
            auto y = remap(0.f, float(res - 1), float(j), 0.f, 1.f);

            mesh.vertices.emplace_back(1.f, x, 1.f - y);
        }
    // -X.
    for (int i = 0; i < res; ++i)
        for (int j = 0; j < res; ++j) {
            auto x = remap(0.f, float(res - 1), float(i), 0.f, 1.f);
            auto y = remap(0.f, float(res - 1), float(j), 0.f, 1.f);

            mesh.vertices.emplace_back(0.f, 1.f - x, y);
        }
    // +Y.
    for (int i = 0; i < res; ++i)
        for (int j = 0; j < res; ++j) {
            auto x = remap(0.f, float(res - 1), float(i), 0.f, 1.f);
            auto y = remap(0.f, float(res - 1), float(j), 0.f, 1.f);

            mesh.vertices.emplace_back(1.f - y, 1.f, x);
        }
    // -Y.
    for (int i = 0; i < res; ++i)
        for (int j = 0; j < res; ++j) {
            auto x = remap(0.f, float(res - 1), float(i), 0.f, 1.f);
            auto y = remap(0.f, float(res - 1), float(j), 0.f, 1.f);

            mesh.vertices.emplace_back(y, 0.f, 1.f - x);
        }
    // +Z.
    for (int i = 0; i < res; ++i)
        for (int j = 0; j < res; ++j) {
            auto x = remap(0.f, float(res - 1), float(i), 0.f, 1.f);
            auto y = remap(0.f, float(res - 1), float(j), 0.f, 1.f);

            mesh.vertices.emplace_back(x, 1.f - y, 1.f);
        }
    // -Z.
    for (int i = 0; i < res; ++i)
        for (int j = 0; j < res; ++j) {
            auto x = remap(0.f, float(res - 1), float(i), 0.f, 1.f);
            auto y = remap(0.f, float(res - 1), float(j), 0.f, 1.f);

            mesh.vertices.emplace_back(1.f - x, y, 0.f);
        }

    return mesh;
}

template<typename F>
auto transformVertices(TriangleMesh& mesh, F&& f) -> void {
    for(auto& vertex : mesh.vertices)
        vertex = f(vertex);
}
