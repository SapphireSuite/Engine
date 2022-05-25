// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_MATERIAL_GUARD
#define SAPPHIRE_ENGINE_ARENDER_MATERIAL_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Render/Base/Material/Bindings/IBOBinding.hpp>
#include <SA/Engine/Render/Base/Material/Bindings/UBOBinding.hpp>
#include <SA/Engine/Render/Base/Material/Bindings/RenderMaterialBindings.hpp>

namespace SA
{
	class ARenderMaterial : protected HardwareInterface
	{
		using HardwareInterface::Clear; // not used.
	};
}

#endif // GUARD
