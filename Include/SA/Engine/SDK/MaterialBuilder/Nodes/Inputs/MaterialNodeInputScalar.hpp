// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_NODE_INPUT_SCALAR_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_NODE_INPUT_SCALAR_GUARD

#include <SA/Engine/SDK/MaterialBuilder/Nodes/Inputs/MaterialNodeInput.hpp>

namespace SA::SDK
{
	class MaterialNodeInputScalar : public MaterialNodeInput
	{
	public:
		float scalar = 0u;
	};
}

#endif // GUARD
