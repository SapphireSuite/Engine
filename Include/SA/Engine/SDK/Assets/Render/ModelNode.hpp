// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MODEL_NODE_GUARD
#define SAPPHIRE_ENGINE_MODEL_NODE_GUARD

#include <vector>
#include <string>

#include <SA/Maths/Matrix/Matrix4.hpp>

#include <SA/Collections/SerializeBinary>

namespace SA
{
	namespace SDK
	{
		struct ModelNode
		{
			Mat4f trMat;
			std::vector<std::string> meshAssetPaths;
		};
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const SDK::ModelNode& _node, std::string& _dst);

		template <>
		bool FromBinary(SDK::ModelNode& _node, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
