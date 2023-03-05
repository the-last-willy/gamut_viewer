#include "window.hpp"

#include <stdexcept>

#include <glad/glad.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void Window::init() {
	/* Initialize the library */
	if(!glfwInit()) {
		throw std::runtime_error("Failed to init GLFW.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

	/* Create a windowed mode window and its OpenGL context */
	handle_ = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if(!handle_) {
		glfwTerminate();
		throw std::runtime_error("Failed to open window.");
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(handle_);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void) io;

	ImGui_ImplGlfw_InitForOpenGL(handle_, true);
	ImGui_ImplOpenGL3_Init("#version 300 es");

	int version = gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress);
	if(version == 0) {
		printf("Failed to initialize OpenGL context\n");
		throw std::runtime_error("Failed to init OpenGL.");
	}
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
