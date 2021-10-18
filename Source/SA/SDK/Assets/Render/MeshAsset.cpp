// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/MeshAsset.hpp>

#include <Core/Algorithms/SizeOf.hpp>
#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
	bool MeshAsset::IsValid() const
	{
		return !raw.vertices.empty() && !raw.indices.empty();
	}

	bool MeshAsset::Load_Internal(Serialize::Reader&& _read, const std::string& _path)
	{
		(void)_path;

		Serialize::FromBinary(raw, _read);
		
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
