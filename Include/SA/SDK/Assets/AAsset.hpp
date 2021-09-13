// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ASSET_AASSET_GUARD
#define SAPPHIRE_ASSET_AASSET_GUARD

#include <SA/Core/Types/Abstract.hpp>

namespace Sa
{
	class AAsset : public Abstract
	{
	protected:
		void CreateDirectory(const std::string& _path) const;

	public:
		virtual bool Load(const std::string& _path) = 0;
		virtual void UnLoad() = 0;

		virtual bool Save(const std::string& _path) const;
	};
}

#endif // GUARD
