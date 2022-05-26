// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_MATERIAL_GUARD
#define SAPPHIRE_ENGINE_ARENDER_MATERIAL_GUARD

#include <cstdint>
#include <string>
#include <unordered_map>

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Render/Base/Material/Bindings/MaterialBindingData.hpp>

namespace SA
{
	class ATexture;
	struct RenderPipelineLayoutDescriptor;
	class ARenderMaterialBindRecorder;

	class ARenderMaterial : protected HardwareInterface
	{
		using HardwareInterface::Create; // overloaded.
		using HardwareInterface::Clear; // not used.

		struct BindMapInfos
		{
			uint32_t binding = 0u;

			uint32_t set = 0u;
		};

		std::unordered_map<std::string, BindMapInfos> mNameToBindingMap;


	protected:
		void Create(const RenderPipelineLayoutDescriptor& _pipLayoutDesc);

		bool GetStaticBindFromNamed(const MaterialNamedBindingInfos& _named, MaterialStaticBindingInfos& _static) const;
	};
}

#endif // GUARD
