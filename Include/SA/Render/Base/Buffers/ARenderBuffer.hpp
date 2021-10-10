// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_BUFFER_GUARD
#define SAPPHIRE_RENDER_ARENDER_BUFFER_GUARD

#include <SA/Render/Base/Buffers/ARenderBufferBase.hpp>

namespace Sa
{
	/**
	*	CPU coherent render buffer.
	*	Easy access and update from CPU.
	*/
	class ARenderBuffer : public ARenderBufferBase
	{

	public:
		void Create(const ARenderDevice* _device,
			RenderBufferType _type,
			uint64 _size) override final;

		virtual void Create(const ARenderDevice* _device,
			RenderBufferType _type,
			uint64 _size,
			const void* _data) = 0;

		virtual void UpdateData(const ARenderDevice* _device, const void* _data, uint64 _size, uint64 _offset = 0u) = 0;
	};
}

#endif // GUARD
