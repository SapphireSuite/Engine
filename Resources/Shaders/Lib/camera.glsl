// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

//{ camera glsl

/**
*   set 1 is engine pre-defined for camera bindings.
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


vec4 ComputeViewPosition(vec4 _modelPosition)
{
    return cameraUBO.proj * cameraUBO.viewInv * _modelPosition;
}

//}
