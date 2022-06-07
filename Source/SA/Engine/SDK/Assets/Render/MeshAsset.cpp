// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/MeshAsset.hpp>

#include <SA/Collections/Debug>

#include <SDK/Assets/AssetManager.hpp>
#include <SDK/Assets/AssetHandle.hpp>

// TODO: remove later.
#include <Render/Base/Mesh/Vertex/Vertex.hpp>


#include <assimp/mesh.h>
#include <assimp/material.h>

namespace SA::SDK
{
//{ Import

	bool MeshAsset::Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos)
	{
		SA_LOG(L"Importing assimp mesh [" << _infos.mesh << L"] from path [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		// Should never happen: aiProcess_Triangulate used on Model import.
		SA_ASSERT(Default, SA/SDK/Asset, _infos.mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE, L"Mesh must be triangle!");

		return
			ImportVertices(_infos) &&
			ImportIndices(_infos) &&
			ImportAABB(_infos) &&
			ImportMaterial(_mgr, _infos);
	}
	
	bool MeshAsset::ImportVertices(const ImportInfos& _infos)
	{
		const aiMesh& mesh = *_infos.mesh;

		// TODO: use import infos for Vertex assembly type.

		raw.vertices.resize(mesh.mNumVertices * sizeof(VertexPNTBT));

		for (uint32_t j = 0u; j < mesh.mNumVertices; ++j)
		{
			const aiVector3D& pos = mesh.mVertices[j];
			const aiVector3D& normal = mesh.mNormals[j];
			const aiVector3D& tangent = mesh.mTangents[j];
			const aiVector3D& bitangent = mesh.mBitangents[j];
			const aiVector3D& texture = mesh.mTextureCoords[0][j];

			new (raw.vertices.data() + j * sizeof(VertexPNTBT)) VertexPNTBT{
				{ Vec3f(pos.x, pos.y, pos.z) },
				{ Vec3f(normal.x, normal.y, normal.z) },
				{ Vec3f(tangent.x, tangent.y, tangent.z) },
				{ Vec3f(bitangent.x, bitangent.y, bitangent.z) },
				{ Vec2f(texture.x, texture.y) }
			};
		}

		return true;
	}
	
	bool MeshAsset::ImportIndices(const ImportInfos& _infos)
	{
		const aiMesh& mesh = *_infos.mesh;

		raw.indices.reserve(mesh.mNumFaces * 3);

		for (uint32_t j = 0u; j < mesh.mNumFaces; ++j)
		{
			const aiFace& face = mesh.mFaces[j];

			raw.indices.insert(raw.indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
		}

		return true;
	}
	
	bool MeshAsset::ImportAABB(const ImportInfos& _infos)
	{
		const aiMesh& mesh = *_infos.mesh;

		const aiVector3D& min = mesh.mAABB.mMin;
		const aiVector3D& max = mesh.mAABB.mMax;
		raw.aabb = AABB3Df(Vec3f(min.x, min.y, min.z), Vec3f(max.x, max.y, max.z));

		return true;
	}
	
	bool MeshAsset::ImportMaterial(AssetMgr& _mgr, const ImportInfos& _infos)
	{
		const std::string pathName = (_infos.outModelBasePath + _infos.matImport.mat->GetName().C_Str()) + "_mat";

		AssetHandle<MaterialAsset> matAsset = _mgr.Import<MaterialAsset>(pathName, _infos.matImport);

		if (matAsset)
			materialPath = pathName;

		return matAsset;
	}

//}
}
