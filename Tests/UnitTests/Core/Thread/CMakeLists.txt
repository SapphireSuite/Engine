# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Projects ===

project(SA-UT_Core_Thread)



# === Inputs ===

# Parse files.
file(GLOB_RECURSE SOURCES "*.cpp")

# Add executable target.
add_executable(SA-UT_Core_Thread ${SOURCES})



# === Dependencies ===

# Unit test module dependency.
target_link_libraries(SA-UT_Core_Thread PUBLIC SA-UnitTestHelper)



# === Tests ===

# Add test.
add_test(NAME CSA-UT_Core_Thread COMMAND SA-UT_Core_Thread --config $<CONFIGURATION> --exe $<TARGET_FILE:SA-UT_Core_Thread>)
