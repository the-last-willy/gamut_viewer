#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window() = default;

	~Window();

	void resize(int w, int h) {
		width = w;
		height = h;
		init();
	}

	bool isOpen() const {
		if(!handle_) {
			return false;
		} else {
			return !glfwWindowShouldClose(handle_);
		}
	}

	void startRendering();

	void stopRendering();

private:
	void init();

	int width = 0;
	int height = 0;

	GLFWwindow *handle_ = nullptr;
};
