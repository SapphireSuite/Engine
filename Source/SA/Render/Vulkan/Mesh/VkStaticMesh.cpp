// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Mesh/VkStaticMesh.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/VkFrame.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void StaticMesh::Create(const Device& _device, CommandBuffer& _cmd, ResourceHolder& _resHold, const RawMesh& _raw)
	{
		AMesh::Create(_raw);

		//// Create Vertex buffer.
		//mVertexBuffer.Create(_device, _cmd, _resHold,
		//	SizeOf(_raw.vertices),
		//	VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		//	_raw.vertices.data());


		//// Create Index buffer.
		//mIndicesSize = SizeOf<uint32>(_raw.indices);
		//mIndexBuffer.Create(_device, _cmd, _resHold,
		//	sizeof(uint32) * mIndicesSize,
		//	VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
		//	_raw.indices.data());
	}
	
	void StaticMesh::Destroy(const Device& _device)
	{
		mVertexBuffer.Destroy(_device);
		mIndexBuffer.Destroy(_device);

		mIndicesSize = ~uint32();
	}


	void StaticMesh::Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos) const
	{
		const Frame& vkFrame = _frame.As<Frame>();

		VkDeviceSize offsets[] = { 0 };
		VkBuffer vkVertBuff = mVertexBuffer;

		vkCmdBindVertexBuffers(vkFrame.cmd, 0, 1, &vkVertBuff, offsets);

		vkCmdBindIndexBuffer(vkFrame.cmd, mIndexBuffer, 0, VK_INDEX_TYPE_UINT32);

		vkCmdDrawIndexed(vkFrame.cmd, mIndicesSize, _infos.instanceNum, 0, 0, 0);
	}
}

#endif
