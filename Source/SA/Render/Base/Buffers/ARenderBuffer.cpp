// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Buffers/ARenderBuffer.hpp>

namespace Sa
{
	void ARenderBuffer::Create(const ARenderDevice* _device,
		RenderBufferType _type,
		uint64 _size)
	{
		Create(_device, _type, _size, nullptr);
	}
}
