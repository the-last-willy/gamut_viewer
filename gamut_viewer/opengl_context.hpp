#pragma once

#include <memory>

class OpenGL_Context {
public:
    virtual ~OpenGL_Context() {}

    virtual void makeCurrent() = 0;
};

class StandaloneOpenGL_Context : public OpenGL_Context {
public:
    StandaloneOpenGL_Context();
    ~StandaloneOpenGL_Context() override;

    void makeCurrent() override;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
