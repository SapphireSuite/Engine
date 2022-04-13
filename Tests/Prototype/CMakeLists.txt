# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_EngineProto)



# Executable

## Add executable target.
add_executable(SA_EngineProto "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_EngineProto PRIVATE SA_Engine)



# Tests

add_test(NAME CSA_EngineProto COMMAND SA_EngineProto)
