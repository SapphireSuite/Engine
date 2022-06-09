// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AMATERIAL_GRAPH_GUARD
#define SAPPHIRE_ENGINE_AMATERIAL_GRAPH_GUARD

#include <SA/Engine/SDK/MaterialBuilder/AMaterialBuilderInterface.hpp>

namespace SA::SDK
{
	class AMaterialGraph
	{
	public:
		virtual void Build(AMaterialBuilderInterface* _builder) = 0;
	};
}

#endif // GUARD
