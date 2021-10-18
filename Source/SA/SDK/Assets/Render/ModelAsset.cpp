// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/ModelAsset.hpp>

#include <vector>

#include <Core/Algorithms/SizeOf.hpp>
#include <Core/Algorithms/MemMove.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Sa
{
	bool ModelAsset::IsValid() const
	{
		return !meshes.empty();
	}

	bool ModelAsset::Load_Internal(Serialize::Reader&& _read, const std::string& _path)
	{
		// TODO: implement.
		(void)_read;
		(void)_path;
		SA_LOG(L"IMPLEMENT", Error, SA/SDK/Asset);
		return false;
	}

	void ModelAsset::UnLoad()
	{
		for (auto mesh : meshes)
			mesh.UnLoad();

		meshes.clear();
	}


	bool ModelAsset::Save_Internal(std::fstream& _fStream) const
	{
		// TODO: implement.
		(void)_fStream;
		SA_LOG(L"IMPLEMENT", Error, SA/SDK/Asset);
		return false;
	}


	bool ModelAsset::Import_Internal(const std::string& _path)
	{
		SA_LOG(L"Importing model {" << _path << L"}", Infos, SA/SDK/Asset);

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(_path, aiProcessPreset_TargetRealtime_MaxQuality);

		if (!scene)
		{
			SA_LOG(L"Assimp Error: " << importer.GetErrorString(), Error, SA/SDK/Asset);
			return false;
		}

		return ParseScene(scene);
	}


	bool ModelAsset::ParseScene(const aiScene* _scene)
	{
		// Materials
		{
			// TODO: Parsing.

			//for (uint32 i = 0u; i < _scene->mNumMaterials; ++i)
			//{
			//	_scene->mMaterials[i];
			//}
		}


		// Animations
		{
			// TODO: Parsing.

			//for (uint32 i = 0u; i < _scene->mNumAnimations; ++i)
			//{
			//	_scene->mAnimations[i];
			//}
		}


		return ParseNode(_scene, _scene->mRootNode);
	}

	bool ModelAsset::ParseNode(const aiScene* _scene, const aiNode* _node)
	{
		// TODO: Add param?
		constexpr VertexComp vImportComp = VertexComp::Default;


		// Parsing meshes of this node.
		for (uint32 i = 0u; i < _node->mNumMeshes; ++i)
		{
			RawMesh& rawMesh = meshes.emplace_back().raw;
			const aiMesh* aiMesh = _scene->mMeshes[_node->mMeshes[i]];

			SA_ASSERT(Default, SA/SDK/Asset, aiMesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE, L"Mesh must be triangle!");


			// Vertices
			{
				std::vector<Vertex<vImportComp>> vertices;
				vertices.reserve(aiMesh->mNumVertices);

				for (uint32 j = 0u; j < aiMesh->mNumVertices; ++j)
				{
					vertices.push_back(Vertex<vImportComp>(
						reinterpret_cast<const Vec3f&>(aiMesh->mVertices[j]),
						reinterpret_cast<const Vec3f&>(aiMesh->mNormals[j]),
						reinterpret_cast<const Vec3f&>(aiMesh->mTangents[j]),
						reinterpret_cast<const Vec3f&>(aiMesh->mTextureCoords[0][j])
					));

					// TODO: Parsing.
					//aiMesh->mBitangents[j];
				}

				const uint32 totalSize = OctSizeOf<uint32>(vertices);

				rawMesh.vertices.resize(totalSize);
				MemMove(reinterpret_cast<const char*>(vertices.data()), rawMesh.vertices.data(), totalSize);
			}


			// Indices
			{
				rawMesh.indices.reserve(aiMesh->mNumFaces * 3);

				for (uint32 j = 0u; j < aiMesh->mNumFaces; ++j)
				{
					const aiFace& face = aiMesh->mFaces[j];

					rawMesh.indices.insert(rawMesh.indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
				}
			}

			
			// Material
			{
				// TODO: Parsing.

				//const aiMaterial* mat = _scene->mMaterials[aiMesh->mMaterialIndex];
			}


			// Bones
			{
				// TODO: Parsing.

				//for (uint32 j = 0u; j < aiMesh->mNumBones; ++j)
				//{
				//	const aiBone* bone = aiMesh->mBones[j];

				//}
			}


			// AABB
			{
				// TODO: Parsing.

				//aiMesh->mAABB;
			}
		}


		// Parsing children nodes.
		for (uint32 i = 0; i < _node->mNumChildren; ++i)
			ParseNode(_scene, _node->mChildren[i]);

		return true;
	}
}