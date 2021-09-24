// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_APIPELINE_GUARD
#define SAPPHIRE_RENDER_APIPELINE_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Base/Pipeline/PipelineCreateInfos.hpp>

namespace Sa
{
	class ARenderDevice;
	class ARenderFrame;

	class APipeline : public Abstract
	{
	public:
		virtual void Create(const ARenderDevice* _device, const PipelineCreateInfos& _infos) = 0;
		virtual void Destroy(const ARenderDevice* _device) = 0;

		virtual void Bind(const ARenderFrame& _frame) const = 0;
	};
}

#endif // GUARD
