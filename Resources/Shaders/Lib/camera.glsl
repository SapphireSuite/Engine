// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

//{ camera glsl

#include <push_constant.glsl>


//{ Bindings

/**
*   set 1 is engine pre-defined for camera bindings.
*/

struct Camera
{
	// Camera projection matrix.
    mat4 proj;
    
	// Camera inverse transformation matrix.
    mat4 viewInv;

    // Camera raw position.
    vec3 position;
};

layout(set = 1, binding = 0) buffer Camera_StorageBuffer
{
    Camera cameras[];
} Camera_UBO;


/*
layout(push_constant) uniform Camera_PushConstants
{
    layout(offset = 0) int cameraIndex;
} Camera_pConst;
*/


//}


//{ Getters

// Get Current camera.
Camera Camera_Get()
{
    return Camera_UBO.cameras[PConst.cameraIndex];
}

// Get Current camera raw position.
vec3 Camera_GetRawPosition()
{
    return Camera_Get().position;
}

//}


vec4 Camera_ComputeViewPosition(vec4 _modelPosition)
{
    Camera cam  = Camera_Get();

    return cam.proj * cam.viewInv * _modelPosition;
}

//}
