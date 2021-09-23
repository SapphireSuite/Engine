// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#version 450

#include <camera.glsl>

// Uniform.

// Object UBO: specific to this shader instance.
layout(binding = 1) uniform ObjectUniformBuffer
{
	// Model transformation matrix.
    mat4 modelMat;

	// Material UV tilling.
    float uvTilling;

	// Material UV offset.
    float uvOffset;

} objectUBO;


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
    vec4 modelPosition = objectUBO.modelMat * vec4(inPosition, 1.0);

    gl_Position = cameraUBO.proj * cameraUBO.viewInv * modelPosition;


    // Texture
    vsOut.texture = inTexture * objectUBO.uvTilling + objectUBO.uvOffset;
}
