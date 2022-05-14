// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Mesh/VkStaticMesh.hpp>

#include <HI/Cast.hpp>
#include <Render/Vulkan/VkFrame.hpp>

namespace SA::VK
{
	void StaticMesh::Create(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw)
	{
		AStaticMesh::Create();

		// Create Vertex buffer.
		mVertexBuffer.Create(_device,
			_init,
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			_raw.vertices.size(),
			_raw.vertices.data());


		// Create Index buffer.
		mIndicesSize = static_cast<uint32_t>(_raw.indices.size());
		mIndexBuffer.Create(_device,
			_init,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
			sizeof(uint32_t) * mIndicesSize,
			_raw.indices.data());
		
		SA_LOG(L"Static Mesh created.", Infos, SA/Engine/Render/Vulkan);
	}
	
	void StaticMesh::Destroy(const Device& _device)
	{
		AStaticMesh::Destroy();

		mVertexBuffer.Destroy(_device);
		mIndexBuffer.Destroy(_device);

		mIndicesSize = ~uint32_t();

		SA_LOG(L"Static Mesh destroyed.", Infos, SA/Engine/Render/Vulkan);
	}


	void StaticMesh::Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos) const
	{
		const Frame& vkFrame = Cast<Frame>(_frame);

		// Bind vertex.
		VkDeviceSize offsets[] = { 0 };
		const VkBuffer& vkVertexBuffer = mVertexBuffer;
		vkCmdBindVertexBuffers(vkFrame.cmd, 0, 1, &vkVertexBuffer, offsets);

		// Bind index.
		vkCmdBindIndexBuffer(vkFrame.cmd, mIndexBuffer, 0, VK_INDEX_TYPE_UINT32);

		// Draw.
		vkCmdDrawIndexed(vkFrame.cmd, mIndicesSize, _infos.instanceNum, 0, 0, 0);
	}
}
