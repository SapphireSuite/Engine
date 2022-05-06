// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

//{ push_constant glsl

/**
*	Bindless push constants.
*	Default value is -1.
*/
layout(push_constant) uniform PConst_PushConstants
{
	int cameraIndex;

	int modelIndex;
	int modelNormalIndex;
} PConst;

//}
