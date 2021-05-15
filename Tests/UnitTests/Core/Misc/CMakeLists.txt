# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Projects ===

project(SA-UT_Core_Misc)



# === Inputs ===

# Parse files.
file(GLOB_RECURSE SOURCES "*.cpp")

# Add executable target.
add_executable(SA-UT_Core_Misc ${SOURCES})



# === Dependencies ===

# Unit test module dependency.
target_link_libraries(SA-UT_Core_Misc PUBLIC SA-UnitTestHelper)

# Add Engine dependency.
target_link_libraries(SA-UT_Core_Misc PRIVATE SA-Engine)



# === Tests ===

# Add test.
add_test(NAME CSA-UT_Core_Misc COMMAND SA-UT_Core_Misc --config $<CONFIGURATION> --exe $<TARGET_FILE:SA-UT_Core_Misc>)
