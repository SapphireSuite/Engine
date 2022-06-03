// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/ModelNode.hpp>

namespace SA
{
	namespace Ser
	{
		template <>
		bool ToBinary(const SDK::ModelNode& _node, std::string& _dst)
		{
			return
				ToBinary(_node.trMat, _dst) &&
				ToBinary(_node.meshAssetPaths, _dst);
		}

		template <>
		bool FromBinary(SDK::ModelNode& _node, const std::string& _src, size_t& _offset)
		{
			return
				FromBinary(_node.trMat, _src, _offset) &&
				FromBinary(_node.meshAssetPaths, _src, _offset);
		}
	}
}
