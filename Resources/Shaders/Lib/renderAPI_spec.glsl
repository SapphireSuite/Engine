// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

//{ renderAPI_spec glsl

/**
*	Vulkan == 1
*	OpenGL == 2
*	DirectX == 3
*/
layout (constant_id = 101) const int renderAPI = 0;


void VulkanAPISpec()
{
    // Coordinate system.
    gl_Position.y = -gl_Position.y;
}


void OpenGLAPISpec()
{
}


void DirectXAPISpec()
{
}


void RenderAPISpec()
{
	if(renderAPI == 1)
		VulkanAPISpec();
	else if(renderAPI == 2)
		OpenGLAPISpec();
	else if(renderAPI == 3)
		DirectXAPISpec();
}


//}
