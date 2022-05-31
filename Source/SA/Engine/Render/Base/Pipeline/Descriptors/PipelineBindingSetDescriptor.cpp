// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Descriptors/PipelineBindingSetDescriptor.hpp>

namespace SA
{
	namespace Ser
	{
		template <>
		bool ToBinary(const PipelineBindingSetDescriptor& _desc, std::string& _dst)
		{
			ToBinary(_desc.bindings, _dst);

			return true;
		}

		template <>
		bool FromBinary(PipelineBindingSetDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			FromBinary(_desc.bindings, _src, _offset);

			return true;
		}
	}
}
