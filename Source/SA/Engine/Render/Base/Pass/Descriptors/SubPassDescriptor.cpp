// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pass/Descriptors/SubPassDescriptor.hpp>

namespace SA
{
	namespace Ser
	{
		template <>
		bool ToBinary(const SubPassDescriptor& _desc, std::string& _dst)
		{
			ToBinary(_desc.sampling, _dst);
			ToBinary(_desc.attachmentDescs, _dst);

			return true;
		}

		template <>
		bool FromBinary(SubPassDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			FromBinary(_desc.sampling, _src, _offset);
			FromBinary(_desc.attachmentDescs, _src, _offset);

			return true;
		}
	}
}
