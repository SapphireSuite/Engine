// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AASSET_GUARD
#define SAPPHIRE_ENGINE_AASSET_GUARD

#include <SA/Engine/SDK/Assets/AssetManager.hpp>

namespace SA::SDK
{
	class AAsset
	{
	protected:
		virtual ~AAsset() = default;

	public:

		/**
		 * @brief Unload asset references from manager.
		 * 
		 * @param _mgr Associated AssetManager.
		 */
		virtual void Unload(AssetMgr& _mgr);

		struct ImportInfos
		{
		};
	};
}

#endif // GUARD
