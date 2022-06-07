// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_ASSET_GUARD
#define SAPPHIRE_ENGINE_ARENDER_ASSET_GUARD

#include <SA/Engine/SDK/Assets/AAsset.hpp>

namespace SA::SDK
{
	class ARenderAsset : public AAsset
	{
	public:
		struct ImportInfos : public AAsset::ImportInfos
		{
		};
	};
}

#endif // GUARD
