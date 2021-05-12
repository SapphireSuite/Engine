# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Projects ===

project(SA-UT_Core_Algorithms)



# === Inputs ===

# Parse files.
file(GLOB_RECURSE SOURCES "*.cpp")

# Add executable target.
add_executable(SA-UT_Core_Algorithms ${SOURCES})



# === Dependencies ===

# Unit test module dependency.
target_link_libraries(SA-UT_Core_Algorithms PUBLIC SA-UnitTestHelper)

# Add Engine dependency.
target_link_libraries(SA-UT_Core_Algorithms PRIVATE SA-Engine)



# === Tests ===

# Add test.
add_test(NAME CSA-UT_Core_Algorithms COMMAND SA-UT_Core_Algorithms --config $<CONFIGURATION> --exe $<TARGET_FILE:SA-UT_Core_Algorithms>)
