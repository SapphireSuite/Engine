// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/MeshAsset.hpp>

#include <SA/Collections/Debug>

#include <Render/Base/Mesh/Vertex/Vertex.hpp>

#include <assimp/mesh.h>

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


	bool MeshAsset::Import(const aiMesh* aiMesh)
	{
		SA_ASSERT(Default, SA/SDK/Asset, aiMesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE, L"Mesh must be triangle!");


		// Vertices
		{
			raw.vertices.resize(aiMesh->mNumVertices * sizeof(VertexPNTBT));

			for (uint32_t j = 0u; j < aiMesh->mNumVertices; ++j)
			{
				const aiVector3D& pos = aiMesh->mVertices[j];
				const aiVector3D& normal = aiMesh->mNormals[j];
				const aiVector3D& tangent = aiMesh->mTangents[j];
				const aiVector3D& bitangent = aiMesh->mBitangents[j];
				const aiVector3D& texture = aiMesh->mTextureCoords[0][j];

				new (raw.vertices.data() + j * sizeof(VertexPNTBT)) VertexPNTBT{
					{ Vec3f(pos.x, pos.y, pos.z) },
					{ Vec3f(normal.x, normal.y, normal.z) },
					{ Vec3f(tangent.x, tangent.y, tangent.z) },
					{ Vec3f(bitangent.x, bitangent.y, bitangent.z) },
					{ Vec2f(texture.x, texture.y) }
				};
			}
		}


		// Indices
		{
			raw.indices.reserve(aiMesh->mNumFaces * 3);

			for (uint32_t j = 0u; j < aiMesh->mNumFaces; ++j)
			{
				const aiFace& face = aiMesh->mFaces[j];

				raw.indices.insert(raw.indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
			}
		}


		// AABB
		{
			const aiVector3D& min = aiMesh->mAABB.mMin;
			const aiVector3D& max = aiMesh->mAABB.mMax;
			raw.aabb = AABB3Df(Vec3f(min.x, min.y, min.z), Vec3f(max.x, max.y, max.z));
		}

		return true;
	}
}
