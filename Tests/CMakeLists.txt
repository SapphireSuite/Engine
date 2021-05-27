# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Compile features ===

# Max warning level for tests.
if(MSVC)
	if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") # ClangCl
		target_compile_options(SA-Engine PUBLIC -W4)
	else()
		target_compile_options(SA-Engine PUBLIC /W4)
	endif()
elseif()
	target_compile_options(SA-Engine PUBLIC -Wall -Wextra)
endif()


# Add Thread sanitizer.
if(UNIX AND NOT APPLE AND (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR SA_CI))
	target_compile_options(SA-Engine PUBLIC -fsanitize=thread)
	target_link_options(SA-Engine PUBLIC -fsanitize=thread)
endif()



# === Entrypoints ===

add_subdirectory(Prototype)
add_subdirectory(UnitTests)
