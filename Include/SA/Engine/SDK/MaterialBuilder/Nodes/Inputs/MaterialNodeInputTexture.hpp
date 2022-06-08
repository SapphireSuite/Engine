// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_NODE_INPUT_TEXTURE_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_NODE_INPUT_TEXTURE_GUARD

#include <string>

#include <SA/Engine/SDK/MaterialBuilder/Nodes/Inputs/MaterialNodeInput.hpp>

namespace SA::SDK
{
	class MaterialNodeInputTexture : public MaterialNodeInput
	{
	public:
		std::string path;
	};
}

#endif // GUARD
