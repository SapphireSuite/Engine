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

		bool ReadFile(const std::string& _path, std::string& _out);

	public:
		bool Open(const std::string& _path);

		virtual bool IsValid() const = 0;

		virtual bool Load(const std::string& _path) = 0;
		virtual void UnLoad() = 0;

		virtual bool Save(const std::string& _path) const;

		virtual bool Import(const std::string& _path) = 0;
	};
}

#endif // GUARD
