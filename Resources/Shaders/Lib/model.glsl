// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

//{ model glsl

/**
*   set 1 is engine-reserved.
*/

layout(set = 1, binding = 1) uniform Model
{
	// Model transformation matrix.
    mat4 transform;

} ModelUBO;


vec4 ComputeModelPosition(vec3 _position)
{
	return ModelUBO.transform * vec4(_position, 1.0);
}

//}
