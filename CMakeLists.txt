cmake_minimum_required(VERSION 3.23)
project(gamut_viewer)

if(MSVC)
	add_compile_options(/W4 /WX /std:c++latest)
	add_link_options(/ignore:4099)
else()
	add_compile_options(-std=c++23)
endif()

find_package(Catch2 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)

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

add_executable(viewer gamut_viewer/window.cpp gamut_viewer/window.hpp gamut_viewer/shader_c.cpp gamut_viewer/shader_c.hpp gamut_viewer/main.cpp)
target_sources(viewer
	PRIVATE)
target_link_libraries(viewer
	PRIVATE
		imgui_opengl3_glfw
		imgui::imgui
		glad)

add_executable(viewer_tests)
target_sources(viewer_tests
	PRIVATE
		gamut_viewer/main.cpp)
target_link_libraries(viewer_tests
	PRIVATE
		Catch2::Catch2)