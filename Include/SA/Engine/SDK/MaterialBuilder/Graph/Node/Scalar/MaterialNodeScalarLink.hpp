// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_NODE_SCALAR_LINK_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_NODE_SCALAR_LINK_GUARD

#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/AMaterialNodeLink.hpp>
#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Scalar/IMaterialScalarNodeLink.hpp>

#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Scalar/IMaterialScalarNode.hpp>

namespace SA::SDK
{
	class MaterialNodeScalarLink :
		public AMaterialNodeLink,
		public IMaterialScalarNodeLink
	{
	public:
		std::shared_ptr<IMaterialScalarNode> node;

		MaterialNodeScalarLink(std::shared_ptr<IMaterialScalarNode> _node = nullptr) noexcept :
			node{ std::move(_node) }
		{
		}
	};
}

#endif // GUARD
