# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Projects ===

project(SA-UT_Core_Types)



# === Inputs ===

# Add executable target.
add_executable(SA-UT_Core_Types "main.cpp")



# === Dependencies ===

# Unit test module dependency.
target_link_libraries(SA-UT_Core_Types PUBLIC SA-UnitTestHelper)

# Add Engine dependency.
target_link_libraries(SA-UT_Core_Types PRIVATE SA-Engine)



# === Tests ===

# Add test.
add_test(NAME CSA-UT_Core_Types COMMAND SA-UT_Core_Types --config $<CONFIGURATION> --exe $<TARGET_FILE:SA-UT_Core_Types>)
