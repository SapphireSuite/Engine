// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_NODE_OP_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_NODE_OP_GUARD

#include <vector>
#include <memory>

#include <SA/Engine/SDK/MaterialBuilder/Nodes/MaterialNode.hpp>

namespace SA::SDK
{
	class MaterialNodeInput;
	class MaterialNodeResult;

	class MaterialNodeOp : public MaterialNode
	{
		std::vector<std::shared_ptr<MaterialNodeInput>> mInputs;

	public:
		using InputIterator = std::vector<std::shared_ptr<MaterialNodeInput>>::iterator;

		MaterialNodeOp() = default;
		MaterialNodeOp(std::vector<std::shared_ptr<MaterialNodeInput>> _inputs);

		void AddEntry(std::shared_ptr<MaterialNodeInput> _input, uint32_t _pos = ~uint32_t());

		/**
		 * @brief 
		 * 
		 * @param _input 
		 * @param bRemoveAllInstance Should remove every instance of _input or only the first found.
		 */
		void RemoveEntry(std::shared_ptr<MaterialNodeInput> _input, bool bRemoveAllInstance = false);
		void RemoveEntry(uint32_t _pos);

		InputIterator begin();
		InputIterator end();
	};
}

#endif // GUARD
