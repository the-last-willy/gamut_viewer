#define IMGUI_IMPL_OPENGL_ES3

#include <gamut_viewer/window.hpp>

#include <glad/glad.h>
#include <imgui.h>

#include <iostream>

void
onOpenGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
					 GLsizei length, const GLchar *message,
					 const void *userParam) {

	(void) source, type, id, severity, length, message, userParam;
	std::cerr << "OpenGL: " << message << std::endl;
}

int main() {
	auto window = Window();
	window.resize(1280, 720);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(&onOpenGLDebugMessage, nullptr);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);

	while(window.isOpen()) {
		window.startRendering();

		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::ShowDemoWindow();


		window.stopRendering();
	}

	return 0;
}
