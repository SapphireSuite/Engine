# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# Projects

project(SA_UnitTestHelper)



# Inputs

### Parse files.
file(GLOB_RECURSE SOURCES "Source/*")

add_library(SA_UnitTestHelper STATIC ${SOURCES})

target_include_directories(SA_UnitTestHelper PUBLIC Include/)

target_link_libraries(SA_UnitTestHelper PUBLIC SA_Engine)



# Options


## Enable log in release.
target_compile_definitions(SA_Engine PUBLIC __SA_LOG_RELEASE)


## Test exit on first failure.
option(SA_UTH_EXIT_ON_FAILURE "Exit on first failure" OFF)

if(SA_UTH_EXIT_ON_FAILURE)
	target_compile_definitions(SA_UnitTestHelper PRIVATE SA_UTH_EXIT_ON_FAILURE)
endif()


## Program pause on exit.
option(SA_UTH_EXIT_PAUSE "Should pause program on exit" OFF)

if(SA_UTH_EXIT_PAUSE)
	target_compile_definitions(SA_UnitTestHelper PRIVATE SA_UTH_EXIT_PAUSE)
endif()
