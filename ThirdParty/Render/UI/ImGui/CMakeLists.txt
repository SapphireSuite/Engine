# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Inputs

add_library(SA_ImGuiDeps INTERFACE)	# Create ImGui dependencies interface.


## Parse files.
file(GLOB IMGUI_SOURCES "imgui/*.cpp")

### Vulkan files & deps
if(SA_VULKAN)
	set(IMGUI_SOURCES "${IMGUI_SOURCES};imgui/backends/imgui_impl_vulkan.cpp")
	target_link_libraries(SA_ImGuiDeps INTERFACE Vulkan::Vulkan)
endif()

### OpenGL files & deps
if(SA_OPEN_GL)
	set(IMGUI_SOURCES "${IMGUI_SOURCES};imgui/backends/imgui_impl_opengl3.cpp")
	# TODO: Add linkage.
endif()

### GLFW files & deps
if(SA_GLFW)
	set(IMGUI_SOURCES "${IMGUI_SOURCES};imgui/backends/imgui_impl_glfw.cpp")
	target_link_libraries(SA_ImGuiDeps INTERFACE glfw)
endif()


## Create static library.
add_library(SA_ImGui STATIC ${IMGUI_SOURCES})

target_link_libraries(SA_ImGui PUBLIC SA_ImGuiDeps)				# Link dependencies.


## Include directories
target_include_directories(SA_ImGui PUBLIC imgui)
target_include_directories(SA_ImGui PUBLIC imgui/backends)
