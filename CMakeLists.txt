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

### Parse files.
file(GLOB_RECURSE SOURCES "Source/*")

### Add static library target.
add_library(SA_Engine STATIC ${SOURCES})

### Link dependencies.
target_link_libraries(SA_Engine PUBLIC SA_EngineDeps)



# Include directories

target_include_directories(SA_Engine PUBLIC Include)
target_include_directories(SA_Engine PRIVATE Include/SA)



# Compile features

## Standard
target_compile_features(SA_Engine PUBLIC c_std_11)
target_compile_features(SA_Engine PUBLIC cxx_std_20)

### SA-Engine module implementation preprocessor.
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

if(NOT SA_USE_SANITIZER AND MSVC)
	# MSVC add sanitizer by default if installed.
	string(REPLACE "-fsanitize=address" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
	string(REPLACE "-fsanitize=address" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()



# Tests

### Enable testing for this directory and below.
enable_testing()



# Entrypoints

add_subdirectory(ThirdParty)

if(SA_ENGINE_BUILD_TESTS)
	add_subdirectory(Tests)
endif()
