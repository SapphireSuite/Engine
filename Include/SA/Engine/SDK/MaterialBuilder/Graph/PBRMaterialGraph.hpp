// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PBR_MATERIAL_GRAPH_GUARD
#define SAPPHIRE_ENGINE_PBR_MATERIAL_GRAPH_GUARD

#include <memory>

#include <SA/Engine/SDK/MaterialBuilder/Graph/MaterialGraph.hpp>

namespace SA::SDK
{
	class MaterialNodeResult;

	class PBRMaterialGraph : public MaterialGraph
	{
	public:
		std::shared_ptr<MaterialNodeResult> baseColor;
		std::shared_ptr<MaterialNodeResult> specular;
		std::shared_ptr<MaterialNodeResult> metallic;
		std::shared_ptr<MaterialNodeResult> roughness;
		std::shared_ptr<MaterialNodeResult> emissive;
		
		std::shared_ptr<MaterialNodeResult> normal;

		std::shared_ptr<MaterialNodeResult> ambiantOcclusion;
	};
}

#endif // GUARD
