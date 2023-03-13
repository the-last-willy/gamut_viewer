#include <gamut_viewer/color.hpp>
#include <gamut_viewer/triangle_mesh.hpp>
#include <gamut_viewer/window.hpp>

#include <glad/glad.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <imgui.h>

#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

std::string fileContent(std::string path) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open file.");
    } else {
        return {
                std::istreambuf_iterator<char>(ifs),
                std::istreambuf_iterator<char>()
        };
    }
}

auto compiledShader(GLenum type, std::string_view filepath) {
    auto shader = glCreateShader(type);
    auto source = fileContent(std::string(filepath));
    auto str = data(source);
    auto size = static_cast<GLint>(std::size(source));
    glShaderSource(shader, 1, &str, &size);
    glCompileShader(shader);
    return shader;
}

auto optCompilationError(GLuint shader) -> std::optional<std::string> {
    GLint status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE)
        return std::nullopt;
    else {
        GLint log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        std::string log(log_length, '\0');
        glGetShaderInfoLog(shader, log_length, nullptr, data(log));
        return log;
    }
}

auto optLinkageError(GLuint program) -> std::optional<std::string> {
    GLint status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_TRUE)
        return std::nullopt;
    else {
        GLint log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        std::string log(log_length, '\0');
        glGetProgramInfoLog(program, log_length, nullptr, data(log));
        return log;
    }
}

int main() {
    auto window = Window();
    window.resize(1280, 720);

    auto cube = ::cube(10);
    for (auto vertex: cube.vertices) {
        for(int i = 0; i < 3; ++i)
            vertex[i] = linear_RGB_to_sRGB(vertex[i]);
        auto avg = dot(vertex, glm::vec3(1.f)) / 3.f;
        cube.colors.push_back(glm::vec3(avg));
    }

    transformVertices(cube, [](glm::vec3 v) {
        v -= glm::vec3(0.5f);
        return normalize(v) + glm::vec3(0.5f);
    });

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * size(cube.vertices),
                 data(cube.vertices), GL_STATIC_DRAW);

    GLuint vcbo = 0;
    glGenBuffers(1, &vcbo);
    glBindBuffer(GL_ARRAY_BUFFER, vcbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * size(cube.colors),
                 data(cube.colors), GL_STATIC_DRAW);

    GLuint ebo = 0;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned) * size(cube.indices),
                 data(cube.indices), GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindVertexBuffer(0, vbo, 0, 3 * sizeof(float));
    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexBuffer(1, vcbo, 0, 3 * sizeof(float));
    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(1, 1);
    glEnableVertexAttribArray(1);

    auto vert_shader = compiledShader(GL_VERTEX_SHADER,
                                      "/run/media/willyj/Data/dev/project/gamut_viewer/gamut_viewer/forward.vert");
    auto frag_shader = compiledShader(GL_FRAGMENT_SHADER,
                                      "/run/media/willyj/Data/dev/project/gamut_viewer/gamut_viewer/forward.frag");

    auto shader_prog = glCreateProgram();
    glAttachShader(shader_prog, vert_shader);
    glAttachShader(shader_prog, frag_shader);
    glLinkProgram(shader_prog);
    auto error = optLinkageError(shader_prog);

    auto wireframeProgram = glCreateProgram();
    {
        auto vert = compiledShader(GL_VERTEX_SHADER,
                                   "/run/media/willyj/Data/dev/project/gamut_viewer/gamut_viewer/wireframe.vert");
        auto geom = compiledShader(GL_GEOMETRY_SHADER,
                                   "/run/media/willyj/Data/dev/project/gamut_viewer/gamut_viewer/wireframe.geom");
        auto frag = compiledShader(GL_FRAGMENT_SHADER,
                                   "/run/media/willyj/Data/dev/project/gamut_viewer/gamut_viewer/wireframe.frag");

        glAttachShader(wireframeProgram, vert);
        glAttachShader(wireframeProgram, geom);
        glAttachShader(wireframeProgram, frag);

        glLinkProgram(wireframeProgram);
        auto error = optLinkageError(wireframeProgram);

    }

    auto vHeading = 3.14152f;

    auto m = glm::translate(glm::mat4(1.f), glm::vec3(-0.5f));
    float aspectRatio = 16.f / 9.f;
    float size = 2.f;
    glm::mat4 p = glm::ortho(-size * aspectRatio, +size * aspectRatio, -size,
                             +size, -10.f, +10.f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glCullFace(GL_FRONT_AND_BACK);

    while (window.isOpen()) {
        window.startRendering();

        glClearDepthf(1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui::ShowDemoWindow();

        vHeading += 0.01f;
        glm::mat4 v = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -2.f))
                      * glm::rotate(glm::mat4(1.f), vHeading,
                                    glm::vec3(0.f, 1., 0.f));
        auto mvp = p * v * m;

        glProgramUniformMatrix4fv(shader_prog, 0, 1, GL_FALSE, &mvp[0][0]);

        glUseProgram(shader_prog);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, cube.indexCount(), GL_UNSIGNED_INT, 0);

        window.stopRendering();
    }

    return 0;
}
