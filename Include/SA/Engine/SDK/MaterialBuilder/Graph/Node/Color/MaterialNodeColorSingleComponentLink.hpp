// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_NODE_COLOR_SINGLE_COMPONENT_LINK_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_NODE_COLOR_SINGLE_COMPONENT_LINK_GUARD

#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Color/MaterialNodeColorLink.hpp>
#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Scalar/IMaterialScalarNodeLink.hpp>

namespace SA::SDK
{
	class MaterialNodeColorSingleComponentLink :
		public MaterialNodeColorLink,
		public IMaterialScalarNodeLink
	{
	public:
		enum class ColorComponent
		{
			R,
			G,
			B,
			A
		};

		ColorComponent comp = ColorComponent::R;

		MaterialNodeColorSingleComponentLink(
			std::shared_ptr<IMaterialColorNode> _node = nullptr,
			ColorComponent _comp = ColorComponent::R) noexcept :
			MaterialNodeColorLink(std::move(_node)),
			comp{ _comp }
		{
		}
	};
}

#endif // GUARD
