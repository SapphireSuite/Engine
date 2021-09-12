# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

cmake_minimum_required(VERSION 3.17)



# === Projects ===

# Create CMake project.
project(SA-Engine)

message("Main directory: ${CMAKE_SOURCE_DIR}")



# === Outputs ===

# Setup output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)		# .exe
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)	# .lib / .a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)	# .dll / .so



# === Inputs ===

# Parse files.
file(GLOB_RECURSE SOURCES "Source/*")

# Add static library target.
add_library(SA-Engine STATIC ${SOURCES})



# === Include directories ===

target_include_directories(SA-Engine PUBLIC Include)
target_include_directories(SA-Engine PRIVATE Include/SA)


# === Compile features ===

# Standard
target_compile_features(SA-Engine PUBLIC c_std_11)
target_compile_features(SA-Engine PUBLIC cxx_std_17)

# SA-Engine module implementation preprocessor.
target_compile_definitions(SA-Engine PUBLIC SA_ENGINE_IMPL)


# Thread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(SA-Engine PUBLIC Threads::Threads)


# std::filesystem.
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "9.0.0")
	target_link_libraries(SA-Engine PUBLIC stdc++fs)
endif()


# SIMD support
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
	target_compile_options(SA-Engine PUBLIC /arch:AVX2)
else()
	target_compile_options(SA-Engine PUBLIC -mavx -mavx2)
endif()


# Advanced MSVC preprocessor required for Core::Debug
# https://docs.microsoft.com/en-us/cpp/preprocessor/preprocessor-experimental-overview
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
	if(${MSVC_TOOLSET_VERSION} LESS 142)
		target_compile_options(SA-Engine PUBLIC /experimental:preprocessor)
	else()
		target_compile_options(SA-Engine PUBLIC /Zc:preprocessor)
	endif()
endif()



# === Options ===

# Add SA-Engine's tests to build tree.
option(SA_ENGINE_BUILD_TESTS "Should build SA-Engine tests" OFF)


# Define continuous integration (CI) preprocessor.
if(SA_CI)
	target_compile_definitions(SA-Engine PUBLIC SA_CI)
endif()



# === Tests ===

# Enable testing for this directory and below.
enable_testing()



# === Entrypoints ===

add_subdirectory(ThirdParty/Libs)

if(SA_ENGINE_BUILD_TESTS)
	add_subdirectory(Tests)
endif()



# === Input Libs ===

# === Rendering ===

# Vulkan.
option(SA_VULKAN "Compile Vulkan Renderer" ON)

if(SA_VULKAN)
	find_package(Vulkan REQUIRED FATAL_ERROR)
	target_link_libraries(SA-Engine PUBLIC Vulkan::Vulkan)
	target_compile_definitions(SA-Engine PUBLIC SA_VULKAN)
endif()

# OpenGL.
option(SA_OPEN_GL "Compile OpenGL Renderer" ON)

if(SA_OPEN_GL)
	target_compile_definitions(SA-Engine PUBLIC SA_OPEN_GL)
endif()


# === Windowing ===

# GLFW.
option(SA_GLFW "Compile GLFW Window Manager" ON)

if(SA_GLFW)
	target_link_libraries(SA-Engine PUBLIC glfw)
	target_include_directories(SA-Engine PRIVATE ThirdParty/Libs/glfw/include)
	target_compile_definitions(SA-Engine PUBLIC SA_GLFW)
endif()

# ImGUI.
target_link_libraries(SA-Engine PUBLIC ImGui)


# === Assets ===

# Assimp
target_link_libraries(SA-Engine PUBLIC assimp::assimp)
