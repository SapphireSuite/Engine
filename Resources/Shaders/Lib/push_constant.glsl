// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

//{ push_constant glsl

/**
*	Bindless push constants.
*	Default value is -1.
*/
layout(push_constant) uniform PushConstants
{
	int cameraIndex;

	int modelIndex;
	int modelNormalIndex;
} pConst;

//}
