// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

//{ normal_map glsl

/**
*	Wheter bitangent should be computed or read.
*	read == 0
*	computed == 1
*/
layout (constant_id = 102) const int NMap_computeBitangent = 1;

struct NMap_TBN
{
	vec3 tangent;
	vec3 bitangent;
	vec3 normal;
};

/**
*	Compute TBN from model matrix.
*	Should be called in Vertex shader.
*/
void NMap_ComputeTBN(mat3 modelNormalMat, inout NMap_TBN _tbn)
{
	_tbn.normal = modelNormalMat * _tbn.normal;
	_tbn.tangent = modelNormalMat * _tbn.tangent;
	
	if(NMap_computeBitangent)
		_tbn.bitangent = modelNormalMat * _tbn.bitangent;
}

/**
*	Compute normal from normal map.
*	Should be called in Fragment shader.
*/
vec3 NMap_ComputeNormalMapping(sampler2D _normalMap, vec2 _textUV, NMap_TBN _tbn)
{
	_tbn.normal = normalize(_tbn.normal);
	_tbn.tangent = normalize(_tbn.tangent);

	if(NMap_computeBitangent)
		_tbn.bitangent = cross(_tbn.normal, _tbn.tangent);
	else
		_tbn.bitangent = normalize(_tbn.bitangent);

	mat3 TBN = mat3(_tbn.tangent, _tbn.bitangent, _tbn.normal);

	return normalize(TBN * (texture(_normalMap, _textUV).rgb * 2.0 - 1.0));
}

//}
