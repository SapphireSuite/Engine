// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#version 450

#include <camera.glsl>
#include <model.glsl>


// In.
layout(location = 0) in vec3 inPosition;
layout(location = 3) in vec2 inTexture;


// Out.
layout(location = 0) out DataBlock
{
	vec2 texture;
} vsOut;


// Code
void main()
{
    // Position.
    vec4 modelPosition = Model_ComputePosition(inPosition);
    gl_Position = Camera_ComputeViewPosition(modelPosition);


    // Texture
    vsOut.texture = inTexture;
}
