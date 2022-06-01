// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AASSET_GUARD
#define SAPPHIRE_ENGINE_AASSET_GUARD

#include <fstream>

namespace SA::SDK
{
	class AAsset
	{
		void CreateDirectory(const std::string& _path) const;

	protected:
		virtual bool Save_Internal(std::fstream& _fstream) const = 0;
		virtual bool Load_Internal(std::string&& _bin) = 0;

	public:
		virtual ~AAsset() = default;

		virtual bool IsValid() const = 0;

		virtual bool Load(const std::string& _path);
		virtual void UnLoad() = 0;

		virtual bool Save(const std::string& _path) const;
	};
}

#endif // GUARD
