// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_OP_ADD_NODE_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_OP_ADD_NODE_GUARD

#include <memory>

#include <SA/Engine/SDK/MaterialGraph/Node/Instructions/AMaterialInstructionNode.hpp>

#include <SA/Engine/SDK/MaterialGraph/Misc/MaterialArrayEntry.hpp>

namespace SA::SDK
{
	template <typename INodeT, typename ILinkT>
	class MaterialOpAddNode :
		public AMaterialInstructionNode,
		public INodeT
	{
	public:
		MaterialArrayEntry<std::shared_ptr<ILinkT>> entries;

		// TODO: implement INodeT interface.
	};

	using MaterialOpAddScalarNode = MaterialOpAddNode<IMaterialScalarNode, IMaterialScalarNodeLink>;
	using MaterialOpAddColorNode = MaterialOpAddNode<IMaterialColorNode, IMaterialColorNodeLink>;
}

#endif // GUARD
