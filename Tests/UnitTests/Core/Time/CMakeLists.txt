# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Projects ===

project(SA-UT_Core_Time)



# === Inputs ===

# Parse files.
file(GLOB_RECURSE SOURCES "*.cpp")

# Add executable target.
add_executable(SA-UT_Core_Time ${SOURCES})



# === Dependencies ===

# Unit test module dependency.
target_link_libraries(SA-UT_Core_Time PUBLIC SA-UnitTestHelper)

# Add Engine dependency.
target_link_libraries(SA-UT_Core_Time PRIVATE SA-Engine)



# === Tests ===

# Add test.
add_test(NAME CSA-UT_Core_Time COMMAND SA-UT_Core_Time --config $<CONFIGURATION> --exe $<TARGET_FILE:SA-UT_Core_Time>)
