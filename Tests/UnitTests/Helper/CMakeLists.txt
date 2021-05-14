# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Projects ===

# Create CMake project.
project(SA-UnitTestHelper)



# === Input ===

# Parse files.
file(GLOB_RECURSE SOURCES "Source/*")

# Add interface library target.
add_library(SA-UnitTestHelper SHARED ${SOURCES})

# Add SA-UnitTestHelper.hpp include directory.
target_include_directories(SA-UnitTestHelper PUBLIC Include/)

target_link_libraries(SA-UnitTestHelper PUBLIC SA-Engine)


# === Option ===

# Test exit on first failure.
option(SA_UTH_EXIT_ON_FAILURE "Exit on first failure" OFF)

if(SA_UTH_EXIT_ON_FAILURE)
	target_compile_definitions(SA-UnitTestHelper PRIVATE SA_UTH_EXIT_ON_FAILURE)
endif()


# Program pause on exit.
option(SA_UTH_EXIT_PAUSE "Should pause program on exit" OFF)

if(SA_UTH_EXIT_PAUSE)
	target_compile_definitions(SA-UnitTestHelper PRIVATE SA_UTH_EXIT_PAUSE)
endif()


## Add SA-UnitTestHelper's examples to build tree.
#option(SA_UTH_BUILD_EXAMPLES "Should build SA-Engine tests" OFF)
