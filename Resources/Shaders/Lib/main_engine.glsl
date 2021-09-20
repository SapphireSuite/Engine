// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

//{ main_engine scrap

#include <engine_constants.glsl>

#ifdef VERTEX

	#include <renderAPI_spec.glsl>

#endif


void main_user();

void main()
{
	main_user();

#ifdef VERTEX

	RenderAPISpec();

#endif
}


//}
