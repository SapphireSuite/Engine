// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/MeshAsset.hpp>

#include <fstream>

#include <Core/Algorithms/SizeOf.hpp>
#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
	bool MeshAsset::IsValid() const
	{
		return !raw.vertices.empty() && !raw.indices.empty();
	}

	bool MeshAsset::Load_Internal(std::string&& _bin)
	{
		Serialize::Reader read = std::move(_bin);

		Serialize::FromBinary(raw, read);
		
		return true;
	}
	
	void MeshAsset::UnLoad()
	{
		raw.Reset();
	}


	bool MeshAsset::Save_Internal(std::fstream& _fStream) const
	{
		_fStream << Serialize::ToBinary(raw);

		return true;
	}


	bool MeshAsset::Import_Internal(const std::string& _path)
	{
		// TODO: Implement.
		(void)_path;

		return false;
	}
}
