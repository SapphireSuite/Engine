// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_NODE_INPUT_COLOR_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_NODE_INPUT_COLOR_GUARD

#include <SA/Engine/SDK/MaterialBuilder/Nodes/Inputs/MaterialNodeInput.hpp>

#include <SA/Engine/Render/Base/Misc/Color.hpp>

namespace SA::SDK
{
	class MaterialNodeInputColor : public MaterialNodeInput
	{
	public:
		Color color;
	};
}

#endif // GUARD
