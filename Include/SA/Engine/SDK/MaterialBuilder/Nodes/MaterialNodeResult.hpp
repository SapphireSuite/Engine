// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_NODE_RESULT_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_NODE_RESULT_GUARD

#include <memory>

#include <SA/Engine/SDK/MaterialBuilder/Nodes/Inputs/MaterialNodeInput.hpp>

namespace SA::SDK
{
	class MaterialNodeOp;

	class MaterialNodeResult : public MaterialNodeInput
	{
	
	public:
		std::shared_ptr<MaterialNodeOp> operation;
		template <typename T>
		void CreateOperation(std::vector<std::shared_ptr<MaterialNodeInput>> _inputs)
		{
			operation = std::make_shared<T>(std::move(_inputs));
		}
	};
}

#endif // GUARD
