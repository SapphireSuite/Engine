// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

//{ model glsl

#include <push_constant.glsl>


//{ Bindings

/**
*   set 2 is engine pre-defined for Model bindings.
*/

layout(set = 2, binding = 0) buffer Model_TransformStorageBuffer
{
	// Model transformation matrix.
	mat4 transforms[];
} Model_TransformUBO;

layout(set = 2, binding = 1) buffer Model_NormalStorageBuffer
{
    // Normal transformation matrix (used for non-uniform scale).
	mat3 normalMats[];
} Model_NormalUBO;


/*
layout(push_constant) uniform Model_PushConstants
{
	layout(offset = 4) int modelIndex;
	layout(offset = 8) int modelNormalIndex;
} Model_pConst;
*/


//}


//{ Getters

// Get Current Model transform.
mat4 Model_GetTransformMat()
{
    return Model_TransformUBO.transforms[PConst.modelIndex + gl_InstanceIndex];
}

// Get Current Model Normal Matrix.
mat3 Model_GetNormalMat()
{
	// No normal index registered: scale is uniform. Use model transform.
	if(PConst.modelNormalIndex == -1)
		return mat3(Model_GetTransformMat());
	else
		return Model_NormalUBO.normalMats[PConst.modelNormalIndex + gl_InstanceIndex];
}

//}


vec4 Model_ComputePosition(vec3 _position)
{
	return Model_GetTransformMat() * vec4(_position, 1.0);
}

//}
