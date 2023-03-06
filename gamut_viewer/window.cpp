#include "window.hpp"

#include <stdexcept>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

void
onOpenGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
					 GLsizei length, const GLchar *message,
					 const void *userParam) {

	(void) source, type, id, severity, length, message, userParam;
	std::cerr << "OpenGL: " << message << std::endl;
}

void Window::init() {
	/* Initialize the library */
	if(!glfwInit()) {
		throw std::runtime_error("Failed to init GLFW.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	handle_ = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if(!handle_) {
		glfwTerminate();
		throw std::runtime_error("Failed to open window.");
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(handle_);

	int version = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	if(version == 0) {
		printf("Failed to initialize OpenGL context\n");
		throw std::runtime_error("Failed to init OpenGL.");
	}

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(&onOpenGLDebugMessage, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL,
						  GL_TRUE);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void) io;

	ImGui_ImplGlfw_InitForOpenGL(handle_, true);
	ImGui_ImplOpenGL3_Init("#version 400");
}

void Window::startRendering() {
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::stopRendering() {
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(handle_);
}

Window::~Window() {
	if(handle_) {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwTerminate();
	}
}
