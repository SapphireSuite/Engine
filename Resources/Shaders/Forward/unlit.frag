// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#version 450


// Uniform.
layout(binding = 2) uniform sampler2D texSampler;


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
	outColor = texture(texSampler, fsIn.texture);

	if(outColor.a < 0.001)
		discard;
}
