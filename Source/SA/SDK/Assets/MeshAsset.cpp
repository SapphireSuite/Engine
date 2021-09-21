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
		std::fstream fStream(_path, std::ios::binary | std::ios_base::in);

		if (!fStream.is_open())
		{
			SA_LOG("Failed to open file {" << _path << L"}!", Error, SA/SDK/Asset);
			return false;
		}


		// Layout.
		{
			VertexComp layout = VertexComp::None;
			fStream.read(reinterpret_cast<char*>(&layout), sizeof(VertexComp));
			raw.SetLayout(layout);
		}


		// Vertices.
		{
			uint32 vSize = 0u;
			fStream.read(reinterpret_cast<char*>(&vSize), sizeof(uint32));

			if (vSize == 0)
			{
				SA_LOG("Parsing file {" << _path << L"} error: Empty vertices.", Error, SA/SDK/Asset);
				return false;
			}

			raw.vertices.resize(vSize);
			fStream.read(raw.vertices.data(), vSize);
		}


		// Indices.
		{
			uint32 iSize = 0u;
			fStream.read(reinterpret_cast<char*>(&iSize), sizeof(uint32));

			if (iSize == 0)
			{
				SA_LOG("Parsing file {" << _path << L"} error: Empty indices.", Error, SA/SDK/Asset);
				return false;
			}

			raw.indices.resize(iSize / sizeof(uint32));
			fStream.read(reinterpret_cast<char*>(raw.indices.data()), iSize);
		}

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


		// Layout.
		fStream.write(reinterpret_cast<const char*>(&raw.GetLayout()->comps), sizeof(VertexComp));


		// Vertices.
		{
			const uint32 vSize = OctSizeOf<uint32>(raw.vertices);
			fStream.write(reinterpret_cast<const char*>(&vSize), sizeof(uint32));
			fStream.write(raw.vertices.data(), vSize);
		}


		// Indices.
		{
			const uint32 iSize = OctSizeOf<uint32>(raw.indices);
			fStream.write(reinterpret_cast<const char*>(&iSize), sizeof(uint32));
			fStream.write(reinterpret_cast<const char*>(raw.indices.data()), iSize);
		}

		return true;
	}


	bool MeshAsset::Import(const std::string& _path)
	{
		// TODO: Implement.
		(void)_path;

		return false;
	}
}
