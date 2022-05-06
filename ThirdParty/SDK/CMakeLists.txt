# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Entrypoints

if(SA_RENDER)
	add_subdirectory(STB)
	add_subdirectory(ShaderBuilder)
endif()

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Skip building assimp tests")
add_subdirectory(assimp)
