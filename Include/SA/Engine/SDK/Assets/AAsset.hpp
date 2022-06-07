// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AASSET_GUARD
#define SAPPHIRE_ENGINE_AASSET_GUARD

namespace SA::SDK
{
	class AssetMgr;

	class AAsset
	{
	protected:
		virtual ~AAsset() = default;

	public:
		struct ImportInfos
		{
		};
	};
}

#endif // GUARD
