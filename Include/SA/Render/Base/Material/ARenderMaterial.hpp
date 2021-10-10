// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_MATERIAL_GUARD
#define SAPPHIRE_RENDER_ARENDER_MATERIAL_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Base/Material/RenderMaterialCreateInfos.hpp>

namespace Sa
{
	class ARenderDevice;

	class ARenderMaterial : public Abstract
	{
	public:
		virtual void Create(const ARenderDevice* _device, const RenderMaterialCreateInfos& _infos) = 0;
		virtual void Destroy(const ARenderDevice* _device) = 0;

		virtual void UpdateBinding(const ARenderDevice* _device, const ARenderMaterialBinding* _bind) = 0;
	};
}

#endif // GUARD
