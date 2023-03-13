#include "opengl_context.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

class StandaloneOpenGL_Context::Impl {
public:
    Impl() {
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW.");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        window_ = glfwCreateWindow(1, 1,
                                   "Standalone OpenGL Context",
                                   nullptr, nullptr);
        if (!window_)
            throw std::runtime_error("Failed to create GLFW window.");

        glfwMakeContextCurrent(window_);

        gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress);
    }

    ~Impl() {
        glfwTerminate();
    }

    void makeCurrent() {
        glfwMakeContextCurrent(window_);
    }

private:
    GLFWwindow *window_ = nullptr;
};

StandaloneOpenGL_Context::StandaloneOpenGL_Context()
        : impl_(std::make_unique<StandaloneOpenGL_Context::Impl>()) {}

StandaloneOpenGL_Context::~StandaloneOpenGL_Context() {}

void StandaloneOpenGL_Context::makeCurrent() {
    impl_->makeCurrent();
}
