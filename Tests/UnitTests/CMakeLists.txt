# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_EngineUT)



# Fetch Google Test.
if(NOT TARGET gtest)

	message("Fetching Google Test...")

	include(FetchContent)


	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG        release-1.11.0
	)

	FetchContent_MakeAvailable(googletest)

endif()



# Executable

## Inputs

file(GLOB_RECURSE SA_ENGINE_UT_SOURCES "*.cpp")

## Add executable target.
add_executable(SA_EngineUT ${SA_ENGINE_UT_SOURCES})



# Dependencies

### Add library dependencies.
target_link_libraries(SA_EngineUT PRIVATE SA_Engine)

### Google test module dependency.
target_link_libraries(SA_EngineUT PRIVATE gtest)



# Tests

add_test(NAME CSA_EngineUT COMMAND SA_EngineUT)
