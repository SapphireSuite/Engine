// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_TEXTURE_VALUE_NODE_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_TEXTURE_VALUE_NODE_GUARD

#include <string>

#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/AMaterialValueNode.hpp>

#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Color/IMaterialColorNode.hpp>

namespace SA::SDK
{
	class MaterialTextureValueNode :
		public AMaterialValueNode,
		public IMaterialColorNode
	{
	public:
		std::string path;
	};
}

#endif // GUARD
