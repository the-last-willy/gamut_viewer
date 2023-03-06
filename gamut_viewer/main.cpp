#define IMGUI_IMPL_OPENGL_ES3

#include <gamut_viewer/window.hpp>

#include <glad/glad.h>
#include <imgui.h>

#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

std::string fileContent(std::string path) {
	std::ifstream ifs(path);
	if(!ifs.is_open()) {
		throw std::runtime_error("Failed to open file.");
	} else {
		return {
			std::istreambuf_iterator<char>(ifs),
			std::istreambuf_iterator<char>()
		};
	}
}

auto optCompilationError(GLuint shader) -> std::optional<std::string> {
	GLint status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_TRUE)
		return std::nullopt;
	else
	{
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
	if(status == GL_TRUE)
		return std::nullopt;
	else
	{
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

//	GLuint vbo = 0;
//	glGenBuffers(1, &vbo);
//	auto vertices = std::vector<float>{
//		0.f, 0.f, 0.f,
//		1.f, 0.f, 0.f,
//		0.f, 1.f, 0.f,
//	};
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size(vertices),
//				 data(vertices), GL_STATIC_DRAW);
//
//	GLuint vao = 0;
//	// glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
//	glBindVertexBuffer(0, vbo, 0, 3 * sizeof(float));
//	glVertexAttribBinding(0, 0);
//	glEnableVertexAttribArray(0);

	auto vert_shader = glCreateShader(GL_VERTEX_SHADER);
//	{
//		auto vert_source = fileContent(
//			"D:\\dev\\project\\gamut_viewer\\gamut_viewer\\forward.vert");
//		auto str = data(vert_source);
//		auto size = static_cast<GLint>(std::size(vert_source));
//		glShaderSource(vert_shader, 1, &str, &size);
//		glCompileShader(vert_shader);
//	}
//
//	auto frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
//	{
//		auto source = fileContent(
//			"D:\\dev\\project\\gamut_viewer\\gamut_viewer\\forward.frag");
//		auto str = data(source);
//		auto size = static_cast<GLint>(std::size(source));
//		glShaderSource(frag_shader, 1, &str, &size);
//		glCompileShader(frag_shader);
//		GLint status;
//		glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &status);
//	}
//
//	auto shader_prog = glCreateProgram();
//	glAttachShader(shader_prog, vert_shader);
//	glAttachShader(shader_prog, frag_shader);
//	glLinkProgram(shader_prog);
//	GLint lstatus;
//	glGetProgramiv(shader_prog, GL_LINK_STATUS, &lstatus);

	while(window.isOpen()) {
		window.startRendering();

		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::ShowDemoWindow();

//		glUseProgram(shader_prog);
//		glBindVertexArray(vao);
//		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.stopRendering();
	}

	return 0;
}
