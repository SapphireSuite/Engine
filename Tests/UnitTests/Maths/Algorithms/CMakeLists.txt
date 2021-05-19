# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Projects ===

project(SA-UT_Maths_Algorithms)



# === Inputs ===

# Parse files.
file(GLOB_RECURSE SOURCES "*.cpp")

# Add executable target.
add_executable(SA-UT_Maths_Algorithms ${SOURCES})



# === Dependencies ===

# Unit test module dependency.
target_link_libraries(SA-UT_Maths_Algorithms PUBLIC SA-UnitTestHelper)



# === Tests ===

# Add test.
add_test(NAME CSA-UT_Maths_Algorithms COMMAND SA-UT_Maths_Algorithms --config $<CONFIGURATION> --exe $<TARGET_FILE:SA-UT_Maths_Algorithms>)
