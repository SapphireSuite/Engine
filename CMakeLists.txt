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

# Add dynamic library target.
add_library(SA-Engine SHARED ${SOURCES})



# === Include directories ===

target_include_directories(SA-Engine PUBLIC Include)
target_include_directories(SA-Engine PRIVATE Include/SA)


# === Compile features ===

# Standard
target_compile_features(SA-Engine PUBLIC c_std_11)
target_compile_features(SA-Engine PUBLIC cxx_std_17)

# SA-Engine module implementation preprocessor.
target_compile_definitions(SA-Engine PUBLIC SA_ENGINE_IMPL)



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

add_subdirectory(ThirdParty)

if(SA_ENGINE_BUILD_TESTS)
	add_subdirectory(Tests)
endif()
