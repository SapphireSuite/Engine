// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/MeshAsset.hpp>

namespace SA::SDK
{
	bool MeshAsset::IsValid() const
	{
		return !raw.vertices.empty() && !raw.indices.empty();
	}

	
	void MeshAsset::UnLoad()
	{
		raw.Clear();
	}
	
	bool MeshAsset::Load_Internal(std::string&& _bin)
	{
		Ser::BinaryStream ser(std::move(_bin));

		ser >> raw;

		return true;
	}

	
	bool MeshAsset::Save_Internal(std::fstream& _fstream) const
	{
		Ser::BinaryStream ser;

		ser << raw;

		_fstream << ser.bin;

		return true;
	}

	
	bool MeshAsset::Import(const std::string& _path)
	{
		// TODO: Implement.
		(void)_path;

		return false;
	}
}
