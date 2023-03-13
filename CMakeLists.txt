cmake_minimum_required(VERSION 3.23)
project(gamut_viewer)

if (MSVC)
    add_compile_options(/W4 /WX /std:c++latest)
    add_link_options(/ignore:4099)
else ()
    add_compile_options(-std=c++23)
endif ()

add_compile_definitions(IMGUI_IMPL_OPENGL_ES3)

find_package(Catch2 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(stb REQUIRED)

include_directories(.)

add_library(imgui_opengl3_glfw)
target_include_directories(imgui_opengl3_glfw
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR})
target_sources(imgui_opengl3_glfw
        PRIVATE
        imgui_impl_glfw.cpp
        imgui_impl_glfw.h
        imgui_impl_opengl3.cpp
        imgui_impl_opengl3.h
        imgui_impl_opengl3_loader.h)
target_link_libraries(imgui_opengl3_glfw
        PUBLIC
        imgui::imgui
        glfw)

add_library(glad)
target_sources(glad
        PRIVATE
        glad/glad.c)

add_library(gamut_viewer_lib gamut_viewer/image.cpp gamut_viewer/image.hpp)
target_sources(gamut_viewer_lib
        PRIVATE
        gamut_viewer/color.cpp
        gamut_viewer/conventions.cpp
        gamut_viewer/opengl_context.cpp
        gamut_viewer/triangle_mesh.cpp
        gamut_viewer/window.cpp)
target_link_libraries(gamut_viewer_lib
        PUBLIC
        imgui_opengl3_glfw
        glad
        glm::glm
        stb::stb)

add_executable(viewer)
target_sources(viewer
        PRIVATE
        gamut_viewer/main.cpp)
target_link_libraries(viewer
        PRIVATE
        gamut_viewer_lib

        imgui_opengl3_glfw
        glad
        glm::glm)

add_executable(viewer_tests)
target_sources(viewer_tests
        PRIVATE
        test/gradients.cpp)
target_link_libraries(viewer_tests
        PRIVATE
        gamut_viewer_lib

        Catch2::Catch2WithMain)
