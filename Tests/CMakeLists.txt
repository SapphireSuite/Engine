# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Compile features ===

# Max warning level for tests.
if(MSVC)
	target_compile_options(SA-Engine PUBLIC /W4)
else()
	target_compile_options(SA-Engine PUBLIC -Wall -Wextra)
endif()



# === Entrypoints ===

add_subdirectory(Prototype)
add_subdirectory(UnitTests)
