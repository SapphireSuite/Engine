// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Mesh/VkStaticMesh.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void StaticMesh::Create(const Device& _device, CommandBuffer& _cmd, ResourceHolder& _resHold, const RawMesh& _rawMesh)
	{
		AMesh::Create(_rawMesh);

		// Create Vertex buffer.
		mVertexBuffer.Create(_device, _cmd, _resHold,
			SizeOf(_rawMesh.vertices),
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			_rawMesh.vertices.data());


		// Create Index buffer.
		mIndicesSize = SizeOf<uint32>(_rawMesh.indices);
		mIndexBuffer.Create(_device, _cmd, _resHold,
			sizeof(uint32) * mIndicesSize,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
			_rawMesh.indices.data());
	}
	
	void StaticMesh::Destroy(const Device& _device)
	{
		mVertexBuffer.Destroy(_device);
		mIndexBuffer.Destroy(_device);

		mIndicesSize = ~uint32();
	}
}

#endif
