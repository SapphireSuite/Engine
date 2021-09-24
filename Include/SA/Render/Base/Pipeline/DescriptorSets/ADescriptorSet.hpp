// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ADESCRIPTOR_SET_GUARD
#define SAPPHIRE_RENDER_ADESCRIPTOR_SET_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Base/Pipeline/DescriptorSets/DescriptorSetCreateInfos.hpp>

namespace Sa
{
	class ARenderFrame;

	class ADescriptorSet : public Abstract
	{
	public:
		virtual void Bind(const ARenderFrame& _frame, const ARenderPipeline& _pipeline) const = 0;
	};
}

#endif // GUARD
