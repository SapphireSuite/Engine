// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ASSET_AASSET_GUARD
#define SAPPHIRE_ASSET_AASSET_GUARD

#include <fstream>

#include <SA/Core/Types/Abstract.hpp>

namespace Sa
{
	class AAsset : public Abstract
	{
		std::string GetFullPath(const std::string& _path) const;
		void CreateDirectory(const std::string& _path) const;

	protected:
		virtual bool Load_Internal(std::string&& _bin) = 0;
		virtual bool Save_Internal(std::fstream& _fStream) const = 0;
		virtual bool Import_Internal(const std::string& _path) = 0;

	public:
		virtual bool IsValid() const = 0;

		bool Open(const std::string& _path);

		bool Load(const std::string& _path);
		virtual void UnLoad() = 0;

		bool Save(const std::string& _path) const;

		bool Import(const std::string& _path);
	};
}

#endif // GUARD
