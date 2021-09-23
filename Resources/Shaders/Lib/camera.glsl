// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

//{ camera glsl

/**
*   set 1 is engine-reserved.
*/

layout(set = 1, binding = 0) uniform Camera
{
	// Camera projection matrix.
    mat4 proj;
    
	// Camera inverse transformation matrix.
    mat4 viewInv;

    // Camera position.
    vec3 viewPosition;
} cameraUBO;

//}
