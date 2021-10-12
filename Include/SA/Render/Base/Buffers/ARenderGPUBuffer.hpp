// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_GPU_BUFFER_GUARD
#define SAPPHIRE_RENDER_ARENDER_GPU_BUFFER_GUARD

#include <SA/Render/Base/Buffers/ARenderBufferBase.hpp>

namespace Sa
{
	/**
	*	Device Local rende buffer.
	*	Allows full GPU optimization but slow access / update from CPU.
	*/
	class ARenderGPUBuffer : public ARenderBufferBase
	{
	public:
		virtual void Create(const ARenderDevice* _device,
			ARenderResourceInitializer& _init,
			RenderBufferType _type,
			uint64 _size,
			const void* _data) = 0;

		virtual void UpdateData(const ARenderDevice* _device, ARenderResourceInitializer& _init, const void* _data, uint64 _size, uint64 _offset = 0) = 0;
	};
}

#endif // GUARD
