// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PBR_MATERIAL_GRAPH_GUARD
#define SAPPHIRE_ENGINE_PBR_MATERIAL_GRAPH_GUARD

#include <SA/Engine/SDK/MaterialGraph/AMaterialGraph.hpp>

namespace SA::SDK
{
	class PBRMaterialGraph : public AMaterialGraph
	{
	public:
		// MaterialLink<IMaterialColorNode> baseColorIn;
		// MaterialLink<IMaterialColorNode> specularIn;
		// MaterialLink<IMaterialScalarNode> metallicIn;
		// MaterialLink<IMaterialScalarNode> roughnessIn;
		// MaterialLink<IMaterialColorNode> normalIn;
		// MaterialLink<IMaterialColorNode> ambientOcclusionIn;

		void Build(AShaderWriter* _writer) override;
	};
}

#endif // GUARD
