// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_ARENDER_ASSET_GUARD
#define SAPPHIRE_SDK_ARENDER_ASSET_GUARD

#include <SA/SDK/Assets/AAsset.hpp>

#include <SA/Render/Base/ARenderResource.hpp>

namespace Sa
{
	class ARenderAsset : public AAsset
	{
	public:
		using ResT = ARenderResource;
	};
}

#endif // GUARD
