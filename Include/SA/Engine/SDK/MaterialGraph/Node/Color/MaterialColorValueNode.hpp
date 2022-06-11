// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_COLOR_VALUE_NODE_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_COLOR_VALUE_NODE_GUARD

#include <SA/Engine/Render/Base/Misc/Color.hpp>

#include <SA/Engine/SDK/MaterialGraph/Node/AMaterialValueNode.hpp>

#include <SA/Engine/SDK/MaterialGraph/Node/Color/IMaterialColorNode.hpp>

namespace SA::SDK
{
	class MaterialColorValueNode :
		public AMaterialValueNode,
		public IMaterialColorNode
	{
	public:
		Color color;

		MaterialColorValueNode(const Color& _color) noexcept :
			color{ _color }
		{
		}
	};
}

#endif // GUARD
