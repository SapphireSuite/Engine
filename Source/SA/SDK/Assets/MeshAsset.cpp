// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/MeshAsset.hpp>

#include <fstream>

#include <Core/Algorithms/SizeOf.hpp>

namespace Sa
{
	bool MeshAsset::IsValid() const
	{
		return !raw.vertices.empty() && !raw.indices.empty();
	}

	bool MeshAsset::Load(const std::string& _path)
	{
		std::string bin;

		if (!ReadFile(_path, bin))
			return false;


		Serialize::Reader read = std::move(bin);

		Serialize::FromBinary(raw, read);
		
		return true;
	}
	
	void MeshAsset::UnLoad()
	{
		raw.Reset();
	}


	bool MeshAsset::Save(const std::string& _path) const
	{
		if (!AAsset::Save(_path))
			return false;


		std::fstream fStream(_path, std::fstream::binary | std::fstream::out | std::fstream::trunc);

		if (!fStream.is_open())
		{
			SA_LOG(L"Failed to open file {" << _path << L"}!", Error, SA/SDK/Asset);
			return false;
		}


		fStream << Serialize::ToBinary(raw);

		return true;
	}


	bool MeshAsset::Import(const std::string& _path)
	{
		// TODO: Implement.
		(void)_path;

		return false;
	}
}
