// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_BUFFER_BASE_GUARD
#define SAPPHIRE_RENDER_ARENDER_BUFFER_BASE_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Base/Buffers/RenderBufferType.hpp>

namespace Sa
{
	class ARenderDevice;
	class ARenderResourceInitializer;

	class ARenderBufferBase : public Abstract
	{
	public:
		class Deleter
		{
			const ARenderDevice* mDevice = nullptr;

		public:
			Deleter(const ARenderDevice* _device) noexcept;

			void operator()(ARenderBufferBase& _buffer);
		};


		virtual bool IsValid() const noexcept = 0;


		virtual void Create(const ARenderDevice* _device,
			RenderBufferType _type,
			uint64 _size) = 0;

		virtual void Destroy(const ARenderDevice* _device) = 0;
	};
}

#endif // GUARD
