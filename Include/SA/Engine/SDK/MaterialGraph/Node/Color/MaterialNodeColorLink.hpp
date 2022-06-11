// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_NODE_COLOR_LINK_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_NODE_COLOR_LINK_GUARD

#include <memory>

#include <SA/Engine/SDK/MaterialGraph/Node/AMaterialNodeLink.hpp>
#include <SA/Engine/SDK/MaterialGraph/Node/Color/IMaterialColorNodeLink.hpp>

#include <SA/Engine/SDK/MaterialGraph/Node/Color/IMaterialColorNode.hpp>

namespace SA::SDK
{
	class MaterialNodeColorLink :
		public AMaterialNodeLink,
		public IMaterialColorNodeLink
	{
	public:
		std::shared_ptr<IMaterialColorNode> node;

		MaterialNodeColorLink(std::shared_ptr<IMaterialColorNode> _node = nullptr) noexcept :
			node{ std::move(_node) }
		{
		}
	};
}

#endif // GUARD
