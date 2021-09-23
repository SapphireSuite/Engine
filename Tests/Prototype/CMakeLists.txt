# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# Projects

project(SA_EngineProto)



# Inputs

### Add executable target.
add_executable(SA_EngineProto "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_EngineProto PRIVATE SA_Engine)



# Tests

add_test(NAME CSA_EngineProto COMMAND SA_EngineProto)
