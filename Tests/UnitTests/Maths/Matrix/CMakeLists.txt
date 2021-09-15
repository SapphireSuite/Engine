# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# Projects

project(SA_UT_Maths_Matrix)



# Inputs

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(SA_UT_Maths_Matrix ${SOURCES})



# Dependencies

### Unit test module dependency.
target_link_libraries(SA_UT_Maths_Matrix PRIVATE SA_UnitTestHelper)



# Tests

add_test(NAME CSA_UT_Maths_Matrix COMMAND SA_UT_Maths_Matrix)
