# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

cmake_minimum_required(VERSION 3.16)



# Project

project(SA_Engine)

message("Main directory: ${CMAKE_SOURCE_DIR}")



# Outputs

### Setup output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)		# .exe
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)		# .lib / .a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)		# .dll / .so



# Input.

set(SA_SOURCE_DIR "Source/SA/Engine")
file(GLOB SA_ENGINE_SOURCES "${SA_SOURCE_DIR}/*")

### Interface library for dependencies.
add_library(SA_EngineDeps INTERFACE)
target_link_libraries(SA_EngineDeps INTERFACE SA_Logger SA_Maths SA_Event)


## Render
option(SA_RENDER "Compile Engine Renderer module" ON)
option(SA_VULKAN "Compile Vulkan Renderer" ON)
option(SA_OPEN_GL "Compile OpenGL Renderer" OFF)

if(SA_RENDER)
	file(GLOB_RECURSE SA_RENDER_BASE_SOURCES "${SA_SOURCE_DIR}/Render/Base/*")

	### Vulkan
	if(SA_VULKAN)
		file(GLOB_RECURSE SA_RENDER_VULKAN_SOURCES "${SA_SOURCE_DIR}/Render/Vulkan/*")

		find_package(Vulkan REQUIRED FATAL_ERROR)
		target_link_libraries(SA_EngineDeps INTERFACE Vulkan::Vulkan)
		target_compile_definitions(SA_EngineDeps INTERFACE SA_VULKAN)
	endif()

	### OpenGL
	if(SA_OPEN_GL)
		file(GLOB_RECURSE SA_RENDER_OPEN_GL_SOURCES "${SA_SOURCE_DIR}/Render/OpenGL/*")

		target_compile_definitions(SA_EngineDeps INTERFACE SA_OPEN_GL)
	endif()

	set(SA_ENGINE_SOURCES "${SA_ENGINE_SOURCES};${SA_RENDER_BASE_SOURCES};${SA_RENDER_VULKAN_SOURCES};${SA_RENDER_OPEN_GL_SOURCES}")
endif()


## Window
option(SA_WINDOW "Compile Engine Windowing module" ON)
option(SA_GLFW "Compile GLFW Window Manager" ON)

if(SA_WINDOW)
	file(GLOB_RECURSE SA_WINDOW_BASE_SOURCES "${SA_SOURCE_DIR}/Window/Base/*")

	### GLFW
	if(SA_GLFW)
		file(GLOB_RECURSE SA_WINDOW_GLFW_SOURCES "${SA_SOURCE_DIR}/Window/GLFW/*")

		target_link_libraries(SA_EngineDeps INTERFACE glfw)
		target_compile_definitions(SA_EngineDeps INTERFACE SA_GLFW)
	endif()

	set(SA_ENGINE_SOURCES "${SA_ENGINE_SOURCES};${SA_WINDOW_BASE_SOURCES};${SA_WINDOW_GLFW_SOURCES}")
endif()


## Input
option(SA_INPUT "Compile Engine Input module" ON)

if(SA_INPUT)
	file(GLOB_RECURSE SA_INPUT_BASE_SOURCES "${SA_SOURCE_DIR}/Input/Base/*")

	### GLFW
	if(SA_GLFW)
		file(GLOB_RECURSE SA_INPUT_GLFW_SOURCES "${SA_SOURCE_DIR}/Input/GLFW/*")

		target_link_libraries(SA_EngineDeps INTERFACE glfw)
		target_compile_definitions(SA_EngineDeps INTERFACE SA_GLFW)
	endif()

	set(SA_ENGINE_SOURCES "${SA_ENGINE_SOURCES};${SA_INPUT_BASE_SOURCES};${SA_INPUT_GLFW_SOURCES}")
endif()


## SDK
option(SA_SDK "Compile Engine SDK module" ON)

if(SA_SDK)
	file(GLOB_RECURSE SA_SDK_SOURCES "${SA_SOURCE_DIR}/SDK/*")

	set(SA_ENGINE_SOURCES "${SA_ENGINE_SOURCES};${SA_SDK_SOURCES}")
endif()



# Library

## Add Static library
add_library(SA_Engine STATIC ${SA_ENGINE_SOURCES})


## Link dependencies.
target_link_libraries(SA_Engine PUBLIC SA_EngineDeps)


## Include directories
target_include_directories(SA_Engine PUBLIC Include)
target_include_directories(SA_Engine PRIVATE Include/SA/Engine)


## Compile features

### Standard
target_compile_features(SA_Engine PUBLIC c_std_11)
target_compile_features(SA_Engine PUBLIC cxx_std_20)

### SA_Engine module implementation preprocessor.
target_compile_definitions(SA_Engine PUBLIC SA_ENGINE_IMPL)



# Options

## Add SA-Engine's tests to build tree.
option(SA_ENGINE_BUILD_TESTS "Should build SA-Engine tests" OFF)



# Entrypoints

add_subdirectory(ThirdParty)

if(SA_ENGINE_BUILD_TESTS_OPT)

	### Enable testing for this directory and below.
	enable_testing()

	add_subdirectory(Tests)
endif()
