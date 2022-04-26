# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_EngineUT)

SA_FetchGoogleTest()



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
