// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Descriptors/PipelineBindingDescriptor.hpp>

namespace SA
{
	PipelineBindingDescriptor::PipelineBindingDescriptor(ShaderBindingDescriptor&& _other) noexcept :
		ShaderBindingDescriptor(std::move(_other))
	{
	}

	PipelineBindingDescriptor::PipelineBindingDescriptor(const ShaderBindingDescriptor& _other) noexcept :
		ShaderBindingDescriptor(_other)
	{
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const PipelineBindingDescriptor& _desc, std::string& _dst)
		{
			ToBinary<ShaderBindingDescriptor>(_desc, _dst);
			ToBinary(_desc.stageFlags, _dst)

			return true;
		}

		template <>
		bool FromBinary(PipelineBindingDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			FromBinary<ShaderBindingDescriptor>(_desc, _src, _offset);
			FromBinary(_desc.stageFlags, _src, _offset)

			return true;
		}
	}
}
