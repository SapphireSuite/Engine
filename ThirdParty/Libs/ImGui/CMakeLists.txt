# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.



# === Inputs ===

# Parse files.
file(GLOB_RECURSE SOURCES "Source/*")

# Create static library.
add_library(ImGui STATIC ${SOURCES})



# === Include directories ===

target_include_directories(ImGui PUBLIC Include)
