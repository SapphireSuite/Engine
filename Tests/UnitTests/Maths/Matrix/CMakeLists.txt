# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Projects ===

project(SA-UT_Maths_Matrix)



# === Inputs ===

# Parse files.
file(GLOB_RECURSE SOURCES "*.cpp")

# Add executable target.
add_executable(SA-UT_Maths_Matrix ${SOURCES})



# === Dependencies ===

# Unit test module dependency.
target_link_libraries(SA-UT_Maths_Matrix PUBLIC SA-UnitTestHelper)

# Add Engine dependency.
target_link_libraries(SA-UT_Maths_Matrix PRIVATE SA-Engine)



# === Tests ===

# Add test.
add_test(NAME CSA-UT_Maths_Matrix COMMAND SA-UT_Maths_Matrix --config $<CONFIGURATION> --exe $<TARGET_FILE:SA-UT_Maths_Matrix>)
