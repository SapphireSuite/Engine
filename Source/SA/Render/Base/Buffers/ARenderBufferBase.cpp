// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Buffers/ARenderBufferBase.hpp>

namespace Sa
{
	ARenderBufferBase::Deleter::Deleter(const ARenderDevice* _device) noexcept :
		mDevice{ _device }
	{
	}

	void ARenderBufferBase::Deleter::operator()(ARenderBufferBase& _buffer)
	{
		_buffer.Destroy(mDevice);
	}
}
