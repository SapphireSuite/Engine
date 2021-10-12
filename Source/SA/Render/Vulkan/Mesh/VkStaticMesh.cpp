// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Mesh/VkStaticMesh.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/VkFrame.hpp>
#include <Render/Vulkan/VkResourceInitializer.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void StaticMesh::Create(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw)
	{
		mLayout = _raw.GetLayout();

		// Create Vertex buffer.
		mVertexBuffer.Create(_device,
			_init,
			RenderBufferType::Vertex,
			SizeOf(_raw.vertices),
			_raw.vertices.data());


		// Create Index buffer.
		mIndicesSize = SizeOf<uint32>(_raw.indices);
		mIndexBuffer.Create(_device,
			_init,
			RenderBufferType::Index,
			sizeof(uint32) * mIndicesSize,
			_raw.indices.data());
		
		SA_LOG(L"Mesh created.", Infos, SA/Render/Vulkan);
	}
	
	void StaticMesh::Destroy(const Device& _device)
	{
		mVertexBuffer.Destroy(_device);
		mIndexBuffer.Destroy(_device);

		mIndicesSize = ~uint32();
		
		SA_LOG(L"Mesh destroyed.", Infos, SA/Render/Vulkan);
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
