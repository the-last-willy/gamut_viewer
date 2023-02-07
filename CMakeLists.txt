cmake_minimum_required(VERSION 3.23)
project(gamut_viewer)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(viewer)
target_sources(viewer
	PRIVATE
		src/main.cpp)
