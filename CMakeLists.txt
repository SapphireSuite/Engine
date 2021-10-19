# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

cmake_minimum_required(VERSION 3.17)



# Project

project(SA_Engine)

message("Main directory: ${CMAKE_SOURCE_DIR}")



# Outputs

### Setup output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)		# .exe
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)	# .lib / .a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)	# .dll / .so



# Inputs

set(SA_SOURCE_DIR "Source/SA")


## Core
file(GLOB_RECURSE SA_SOURCES "${SA_SOURCE_DIR}/Core/*")


## Maths
option(SA_MATHS "Compile Engine Maths module" ON)

if(SA_MATHS)
	file(GLOB_RECURSE SA_MATHS_SOURCES "${SA_SOURCE_DIR}/Maths/*")
	set(SA_SOURCES "${SA_SOURCES};${SA_MATHS_SOURCES}")
endif()


## Render
option(SA_RENDER "Compile Engine Renderer module" ON)
option(SA_VULKAN "Compile Vulkan Renderer" ON)
option(SA_OPEN_GL "Compile OpenGL Renderer" OFF)

if(SA_RENDER)
	file(GLOB_RECURSE SA_RENDER_BASE_SOURCES "${SA_SOURCE_DIR}/Render/Base/*")

	### Vulkan
	if(SA_VULKAN)
		file(GLOB_RECURSE SA_RENDER_VULKAN_SOURCES "${SA_SOURCE_DIR}/Render/Vulkan/*")
	endif()

	### OpenGL
	if(SA_OPEN_GL)
		file(GLOB_RECURSE SA_RENDER_OPEN_GL_SOURCES "${SA_SOURCE_DIR}/Render/OpenGL/*")
	endif()

	set(SA_SOURCES "${SA_SOURCES};${SA_RENDER_BASE_SOURCES};${SA_RENDER_VULKAN_SOURCES};${SA_RENDER_OPEN_GL_SOURCES}")
endif()


## Window
option(SA_WINDOW "Compile Engine Windowing module" ON)
option(SA_GLFW "Compile GLFW Window Manager" ON)

if(SA_WINDOW)
	file(GLOB_RECURSE SA_WINDOW_BASE_SOURCES "${SA_SOURCE_DIR}/Window/Base/*")
	file(GLOB_RECURSE SA_INPUT_BASE_SOURCES "${SA_SOURCE_DIR}/Input/Base/*")
	set(SA_SOURCES "${SA_SOURCES};${SA_WINDOW_BASE_SOURCES};${SA_INPUT_BASE_SOURCES}")

	### GLFW
	if(SA_GLFW)
		file(GLOB_RECURSE SA_WINDOW_GLFW_SOURCES "${SA_SOURCE_DIR}/Window/GLFW/*")
		file(GLOB_RECURSE SA_INPUT_GLFW_SOURCES "${SA_SOURCE_DIR}/Input/GLFW/*")
		set(SA_SOURCES "${SA_SOURCES};${SA_WINDOW_GLFW_SOURCES};${SA_INPUT_GLFW_SOURCES}")
	endif()
endif()


## SDK
option(SA_SDK "Compile Engine SDK module" ON)

if(SA_SDK)
	file(GLOB_RECURSE SA_SDK_SOURCES "${SA_SOURCE_DIR}/SDK/*")
	set(SA_SOURCES "${SA_SOURCES};${SA_SDK_SOURCES}")
endif()



# Library

## Add Static library
add_library(SA_Engine STATIC ${SA_SOURCES})


## Link dependencies.
target_link_libraries(SA_Engine PUBLIC SA_EngineDeps)


## Include directories

target_include_directories(SA_Engine PUBLIC Include)
target_include_directories(SA_Engine PRIVATE Include/SA)


## Compile features

### Standard
target_compile_features(SA_Engine PUBLIC c_std_11)
target_compile_features(SA_Engine PUBLIC cxx_std_20)

### SA_Engine module implementation preprocessor.
target_compile_definitions(SA_Engine PUBLIC SA_ENGINE_IMPL)



# Options

## Add SA-Engine's tests to build tree.
option(SA_ENGINE_BUILD_TESTS "Should build SA-Engine tests" OFF)


## Define continuous integration (CI) preprocessor.
if(SA_CI)
	target_compile_definitions(SA_Engine PUBLIC SA_CI)
endif()


## Enable sanitizer
option(SA_USE_SANITIZER "Use sanitizer" OFF)



# Tests

### Enable testing for this directory and below.
enable_testing()



# Entrypoints

add_subdirectory(ThirdParty)

if(SA_ENGINE_BUILD_TESTS)
	add_subdirectory(Tests)
endif()
