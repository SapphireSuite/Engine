// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#version 450


// Uniform.
layout(binding = 0) uniform sampler2D albedo;


// In.
layout(location = 0) in DataBlock
{
	vec2 texture;
} fsIn;


// Out.
layout(location = 0) out vec4 outColor;


// Code.
void main()
{
	outColor = texture(albedo, fsIn.texture);

	if(outColor.a < 0.001)
		discard;
}
