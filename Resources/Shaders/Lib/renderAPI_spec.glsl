// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

//{ renderAPI_spec scrap


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
