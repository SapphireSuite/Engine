# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

# Options

### Additionnal options for tests.
if(MSVC)

	if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") # ClangCl

		# Max warning level.
		target_compile_options(SA_Engine PUBLIC -W4)

	else()

		# Max warning level.
		target_compile_options(SA_Engine PUBLIC /W4)

	endif()

else()

	# Max warning level.
	target_compile_options(SA_Engine PUBLIC -Wall -Wextra)

endif()



# Entrypoints

add_subdirectory(Prototype)
add_subdirectory(UnitTests)
