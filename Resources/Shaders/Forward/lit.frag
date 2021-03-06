// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#version 450
#extension GL_ARB_separate_shader_objects : enable


// Uniform.
/*
*	0. albedo
*	1. normalMap
*	2. heightMap
*	3. metallicMap
*	4. roughMap
*	5. ambiantOcclusion.
*/
layout(binding = 2) uniform sampler2D texSamplers[6];


layout(binding = 3) uniform MaterialConstants
{
	// Ambient constant.
	vec3 ambient;
	
	// Transparency.
	float alpha;

	// Diffuse constant.
    vec3 diffuse;

	float shininess;

	// Specular constant.
	vec3 specular;

	float metallic;

	// Emissive constant.
	vec3 emissive;

	// Optical density (Refractive index).
	float refraction;

	// Fresnel reflectance.
	float reflectance;
} matConsts;


// Directionnal Light.
struct DirectionnalLight
{
	vec3 direction;

	bool bEnabled;

	vec3 color;
	
	float intensity;

	float ambient;
	float diffuse;
	float specular;
};

layout(binding = 4) buffer DirectionnalLightBuffer
{
	DirectionnalLight lights[];
} dLightBuffer;


// Point Light.
struct PointLight
{
	vec3 position;

	bool bEnabled;

	vec3 color;
	
	float intensity;

	float range;

	float ambient;
	float diffuse;
	float specular;
};

layout(binding = 5) buffer PointLightBuffer
{
	PointLight lights[];
} pLightBuffer;


// Spot Light.
struct SpotLight
{
	vec3 position;

	bool bEnabled;

	vec3 direction;

	float cutOff;

	vec3 color;
	
	float intensity;

	float range;

	float ambient;
	float diffuse;
	float specular;
};

layout(binding = 6) buffer SpotLightBuffer
{
	SpotLight lights[];
} sLightBuffer;


// IBL.
layout(binding = 7) uniform samplerCube skybox;
layout(binding = 8) uniform samplerCube irradianceMap;
layout(binding = 9) uniform sampler2D lookupTableBRDF;


// Constants.
const float PI = 3.14159265359;

// Flags.
const int lightingFlag = 1 << 0;
const int IBLFlag = 1 << 1;

layout(constant_id = 0) const int alphaModel = 0;
layout(constant_id = 1) const int flags = 0;


// In.
layout(location = 0) in DataBlock
{
    vec3 position;
	vec3 normal;
	vec3 tangent;
	vec2 texture;

	vec3 viewPosition;
} fsIn;


// Out.
layout(location = 0) out vec4 outColor;


// Code.
void ComputeAlpha();
void ComputeIllumination();


void main()
{
	// Compute alpha first (alpha channel used in illumination).
	ComputeAlpha();

	// Compute each light on the fragment (forward rendering).
	ComputeIllumination();
}



// === Alpha ===
void ComputeAlpha()
{
	// Alpha model.

	// Opaque.
	if(alphaModel == 0)
	{
		outColor.a = 1.0;
		return;
	}


	// Allows transparency.
	outColor.a = texture(texSamplers[0], fsIn.texture).a * matConsts.alpha;

	if(outColor.a < 0.001)
		discard;
}



// === Illumination ===
struct IlluminationData
{
	// Albedo from texture.
	vec3 albedo;

	// Metallic from texture.
	float metallic;

	// Roughness from texture.
	float roughness;


	// Normal vector.
	vec3 vNormal;

	// Object to camera direction.
	vec3 vCam;
	
	// Object to light direction.
	vec3 vLight;

	// Fresnel reflectance.
	vec3 f0;
};

struct LightData
{
	vec3 color;

	// Light components.
	float ambient;
	float diffuse;
	float specular;


	// Attenuation components.
	vec3 position;
	
	float range;
	
	bool bAttenuation; // Should apply attenuation.


	// Is light is cut off.
	bool bCutOff;
};

vec3 ComputeIBL(inout IlluminationData _data);
void ComputeLights(inout IlluminationData _data);


void ComputeIllumination()
{
//	if(flags & lightingFlag == 0)
//		return;


	IlluminationData data;
	outColor.xyz = vec3(0);

	// Textures.
	data.albedo = texture(texSamplers[0], fsIn.texture).xyz;
	data.metallic = texture(texSamplers[3], fsIn.texture).r;
	data.roughness = texture(texSamplers[4], fsIn.texture).r;


	// === Normal vector ===
	data.vNormal = vec3(0.0);

	if(texture(texSamplers[1], fsIn.texture).rgb != vec3(0))
	{
		// Normal mapping.

		vec3 N = normalize(fsIn.normal);
		vec3 T = normalize(fsIn.tangent);
		vec3 B = cross (N, T);
		mat3 TBN = mat3(T, B, N);
		data.vNormal = normalize(TBN * (texture(texSamplers[1], fsIn.texture).rgb * 2.0 - 1.0));
	}
	else
		data.vNormal = normalize(fsIn.normal); // Vertex normal.


	// === Object to camera direction ===
	data.vCam = normalize(fsIn.viewPosition - fsIn.position);


	// === Fresnel reflectance ===
	data.f0 = mix(vec3(0.16 * matConsts.reflectance * matConsts.reflectance), data.albedo, matConsts.metallic);


//	if(flags & IBLFlag == 0)
		outColor.xyz = ComputeIBL(data);

	ComputeLights(data);
}

float DistributionGGX(float cosAlpha, float _roughness)
{
	// Normal distribution function: GGX model.
	float roughSqr = _roughness * _roughness;

	float denom = cosAlpha * cosAlpha * (roughSqr - 1.0) + 1.0;

    return roughSqr / (PI * denom * denom);
}

float GeometrySchlickGGX(float cosRho, float _roughness)
{
	// Geometry distribution function: GGX model.

	float k = ((_roughness + 1.0) * (_roughness + 1.0)) / 8.0;

    return cosRho / (cosRho * (1.0 - k) + k);
}
  
float GeometrySmith(float cosTheta, float cosRho, float _roughness)
{
    float ggx1 = GeometrySchlickGGX(cosRho, _roughness);
    float ggx2 = GeometrySchlickGGX(cosTheta, _roughness);
	
    return ggx1 * ggx2;
}

vec3 Fresnel(vec3 _f0, float _cosTheta, float _roughness)
{
	// Schlick's approximation.
	return _f0 + (max(vec3(1.0 - _roughness), _f0) - _f0) * pow(1.0 - _cosTheta, 5.0);
}

float ComputeAttenuation(vec3 _lightPosition, float _lightRange)
{
	float distance = length(_lightPosition - fsIn.position);

	return max(1 - (distance / _lightRange), 0.0);
}

vec3 ComputeIBL(inout IlluminationData _data)
{
	// === Specular component ===
	const float MAX_REFLECTION_LOD = 5.0;
	
	float cosAlpha = max(dot(_data.vCam, _data.vNormal), 0.0);

	vec3 kS = Fresnel(_data.f0, cosAlpha, _data.roughness);

	vec3 refl = reflect(-_data.vCam, _data.vNormal);
	vec3 prefilteredColor = textureLod(skybox, refl, _data.roughness * MAX_REFLECTION_LOD).rgb;
	vec2 envBRDF  = texture(lookupTableBRDF, vec2(cosAlpha, _data.roughness)).rg;
	vec3 specular = prefilteredColor * (kS * envBRDF.x + envBRDF.y);


	// === Diffuse component ===
	vec3 irradiance = texture(irradianceMap, _data.vNormal).xyz;

	vec3 kD = (1.0 - kS) * (1.0 - _data.metallic);
	vec3 diffuse = kD * irradiance * matConsts.diffuse * _data.albedo;


	// === Ambient component ===
	float ambiantOccl = texture(texSamplers[5], fsIn.texture).r;

	// TODO: CLEAN LATER: missing ao map.
	if(ambiantOccl == 0.0)
		ambiantOccl = 1.0;


	// Output.
	return (diffuse + specular) * ambiantOccl;
}

vec3 ComputeIlluminationModel(inout IlluminationData _data, inout LightData _lData)
{
	float cosTheta = dot(_data.vNormal, _data.vLight);

	// Transparency Fix.
	if(outColor.a < 1.0 && cosTheta < 0.0)
	{
		_data.vNormal *= -1;
		cosTheta *= -1;
	}


	// === Ambient component ===
	vec3 rA = _lData.color * _lData.ambient * matConsts.ambient * _data.albedo; // ambient radiance.
	

	// === BRDF ===
	vec3 BRDF = vec3(0.0);

	// Check facing: no lighting.
	if(cosTheta > 0.0 && !_lData.bCutOff)
	{
		// === Specular component ===
		// Halfway vector.
		vec3 vHalf = normalize(_data.vLight + _data.vCam);

		// Blinn-Phong variant. Phong formula is: dot(vNormal, vCam)
		float cosAlpha = dot(_data.vNormal, vHalf);
		float cosRho = dot(_data.vNormal, _data.vCam);

		vec3 F = Fresnel(_data.f0, dot(_data.vCam, vHalf), _data.roughness);
		vec3 specularBRDF = vec3(0);

		if(cosAlpha > 0.0 && cosRho > 0.0)
		{
			float NDF = DistributionGGX(cosAlpha, _data.roughness);
			float G = GeometrySmith(cosTheta, cosRho, _data.roughness);
		
			specularBRDF = _lData.color * _lData.specular * matConsts.specular * (NDF * G * F) / (4.0 * cosTheta * cosRho);
		}

		// === Diffuse Component ===
		vec3 kD = (vec3(1.0) - F) * (1.0 - _data.metallic);
		vec3 diffuseBRDF = kD * _lData.color * _lData.diffuse * matConsts.diffuse * _data.albedo / PI;

		// === BRDF sum ===
		BRDF = (diffuseBRDF + specularBRDF) * cosTheta;
	}

	//  === Output ===
	vec3 result = rA + BRDF;

	// Apply attenuation.
	if(_lData.bAttenuation)
		result *= ComputeAttenuation(_lData.position, _lData.range);

	return result;





//	// === Diffuse component ===
//	vec3 Rd = _lData.color * _lData.diffuse * matConsts.diffuse * mix(_data.albedo, vec3(0.0), _data.metallic);
//
//	vec3 diffuseBRDF = Rd/* / PI*/;
//
//
//	// === Specular component ===
//	vec3 specularBRDF = vec3(0);
//
//	// Halfway vector.
//	vec3 vHalf = normalize(_data.vLight + _data.vCam);
//
//	// Blinn-Phong variant. Phong formula is: dot(vNormal, vCam)
//	float cosAlpha = dot(_data.vNormal, vHalf);
//
//	if(cosAlpha > 0.0)
//	{
//		vec3 Rs = _lData.color * _lData.specular * matConsts.specular * mix(vec3(1.0), _data.albedo, _data.metallic);
//
//		/* 
//		*	Normalization factor: Gotanda approximation.
//		*	Source: http://research.tri-ace.com/Data/course_note_practical_implementation_at_triace.pdf
//		*/
//		//float normFactor = 0.0397436 * matConsts.shininess + 0.0856832;
//		float normFactor = (matConsts.shininess + 2) / (4 /** PI*/ * (2 - pow(2, -matConsts.shininess / 2)));
//
//		// Geometric factor: Neumann "Albedo pumped-up".
//		float G = 1.0 / max(cosTheta, dot(_data.vNormal, _data.vCam));
//
//
//		specularBRDF = Rs * normFactor * Fresnel(_data.f0, dot(_data.vCam, vHalf), _data.roughness) * G * pow(cosAlpha, matConsts.shininess);
//	}
//
//
//	// === BRDF sum ===
//	vec3 BRDF = (diffuseBRDF + specularBRDF) * cosTheta;
//
//	// Apply attenuation.
//	if(_lData.bAttenuation)
//		BRDF *= ComputeAttenuation(_lData.position, _lData.range);
//
//
//	//  Output.
//	return rA + BRDF;
}


vec3 ComputeDirectionnalLight(DirectionnalLight _light, inout IlluminationData _data)
{
	// Object to light direction.
	_data.vLight = normalize(-_light.direction);

	// Fill light data.
	LightData lData;
	lData.color = _light.color * _light.intensity;

	lData.ambient = _light.ambient;
	lData.diffuse = _light.diffuse;
	lData.specular = _light.specular;

	lData.bAttenuation = false;
	lData.bCutOff = false;

	return ComputeIlluminationModel(_data, lData);
}

vec3 ComputePointLight(PointLight _light, inout IlluminationData _data)
{
	// Object to light direction.
	_data.vLight = normalize(_light.position - fsIn.position);

	// Fill light data.
	LightData lData;
	lData.color = _light.color * _light.intensity;
	
	lData.ambient = _light.ambient;
	lData.diffuse = _light.diffuse;
	lData.specular = _light.specular;
	
	lData.bAttenuation = true;
	lData.position = _light.position;
	lData.range = _light.range;

	lData.bCutOff = false;

	return ComputeIlluminationModel(_data, lData);
}

vec3 ComputeSpotLight(SpotLight _light, inout IlluminationData _data)
{
	// Object to light direction.
	_data.vLight = normalize(_light.position - fsIn.position);

	// Fill light data.
	LightData lData;
	lData.color = _light.color * _light.intensity;

	lData.ambient = _light.ambient;

	float theta = dot(_data.vLight, normalize(_light.direction));

	// Fragment not in spot light.
	if(theta < _light.cutOff)
		lData.bCutOff = true;
	else
	{
		lData.diffuse = _light.diffuse;
		lData.specular = _light.specular;

		lData.bAttenuation = true;
		lData.position = _light.position;
		lData.range = _light.range;

		lData.bCutOff = false;
	}

	return ComputeIlluminationModel(_data, lData);
}


void ComputeLights(inout IlluminationData _data)
{
	// Directionnal Lights.
	for(int i = 0; i < dLightBuffer.lights.length(); ++i)
	{
		if(dLightBuffer.lights[i].bEnabled)
			outColor.xyz += ComputeDirectionnalLight(dLightBuffer.lights[i], _data);
	}

	// Point Lights.
	for(int i = 0; i < pLightBuffer.lights.length(); ++i)
	{
		if(pLightBuffer.lights[i].bEnabled)
			outColor.xyz += ComputePointLight(pLightBuffer.lights[i], _data);
	}


	// Spot Lights.
	for(int i = 0; i < sLightBuffer.lights.length(); ++i)
	{
		if(sLightBuffer.lights[i].bEnabled)
			outColor.xyz += ComputeSpotLight(sLightBuffer.lights[i], _data);
	}
}
