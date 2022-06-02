// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AASSET_GUARD
#define SAPPHIRE_ENGINE_AASSET_GUARD

#include <string>

namespace SA::SDK
{
	class AssetMgr;

	class AAsset
	{
		friend AssetMgr;

	protected:
		virtual ~AAsset() = default;

		virtual bool Load(AssetMgr& _mgr, const std::string& _path, std::string&& _bin) = 0;
		virtual bool Save(AssetMgr& _mgr, const std::string& _path, std::string& _bin) const = 0;
	};
}

#endif // GUARD
