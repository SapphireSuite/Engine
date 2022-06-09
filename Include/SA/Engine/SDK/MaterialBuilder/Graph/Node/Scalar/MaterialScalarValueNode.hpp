// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_SCALAR_VALUE_NODE_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_SCALAR_VALUE_NODE_GUARD

#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/AMaterialValueNode.hpp>
#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Scalar/IMaterialScalarNode.hpp>

namespace SA::SDK
{
	class MaterialScalarValueNode :
		public AMaterialValueNode,
		public IMaterialScalarNode
	{
	public:
		float scalar = 0.0f;

		MaterialScalarValueNode(float _scalar = 0.0f) noexcept :
			scalar{ _scalar }
		{
		}
	};
}

#endif // GUARD
