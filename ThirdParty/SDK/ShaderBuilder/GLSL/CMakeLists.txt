# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Inputs

add_library(SA_GLSL_ShaderBuilder INTERFACE)



# Entrypoints

## SPIRV
set(SPIRV_SKIP_TESTS ON CACHE BOOL "Skip building SPIRV tests")
set(SPIRV_SKIP_EXECUTABLES ON CACHE BOOL "Skip building SPIRV executables")


## SPIRV-Headers
add_subdirectory(SPIRV-Headers) # Requiered for SPIRV-Tools.
target_link_libraries(SA_GLSL_ShaderBuilder INTERFACE SPIRV-Headers)


## SPIRV-Tools
add_subdirectory(SPIRV-Tools)
target_link_libraries(SA_GLSL_ShaderBuilder INTERFACE SPIRV-Tools)


## SPIRV-Cross
set(SPIRV_CROSS_ENABLE_TESTS OFF CACHE BOOL "Disable SPIRV-Cross tests")

# if(SA_USE_SANITIZER)
# 	set(SPIRV_CROSS_SANITIZE_ADDRESS ON CACHE BOOL "Enable SPIRV-Cross address sanitizer")
# endif()

add_subdirectory(SPIRV-Cross)
target_link_libraries(SA_GLSL_ShaderBuilder INTERFACE spirv-cross-cpp)


## glslang
set(BUILD_TESTING OFF CACHE BOOL "Skip building glslang tests")
set(ENABLE_CTEST OFF CACHE BOOL "Skip building glslang tests")
add_subdirectory(glslang)
target_link_libraries(SA_GLSL_ShaderBuilder INTERFACE glslang)


## shaderc
set(SHADERC_SKIP_EXAMPLES ON CACHE BOOL "Skip building shaderc examples")
set(SHADERC_SKIP_TESTS ON CACHE BOOL "Skip building shaderc tests")
add_subdirectory(shaderc)
target_link_libraries(SA_GLSL_ShaderBuilder INTERFACE shaderc shaderc_util)
