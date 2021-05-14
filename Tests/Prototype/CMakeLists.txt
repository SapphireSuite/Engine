# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Projects ===

project(SA-Engine_Prototype)



# === Inputs ===

# Add executable target.
add_executable(SA-Engine_Prototype "main.cpp")



# === Dependencies ===

# Add library dependencies.
target_link_libraries(SA-Engine_Prototype PRIVATE SA-UnitTestHelper)



# === Tests ===

# Add test.
add_test(NAME CSA-Engine_Prototype COMMAND SA-Engine_Prototype --config $<CONFIGURATION> --exe $<TARGET_FILE:SA-Engine_Prototype>)
