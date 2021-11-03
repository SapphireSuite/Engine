// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Mesh/VkStaticMesh.hpp>

#include <Core/Algorithms/Cast.hpp>
#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/VkFrame.hpp>
#include <Render/Vulkan/VkResourceInitializer.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
	void StaticMesh::Create(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw)
	{
		mLayout = _raw.GetLayout();

		// Create Vertex buffer.
		mVertexBuffer.Create(_device,
			_init,
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			SizeOf(_raw.vertices),
			_raw.vertices.data());


		// Create Index buffer.
		mIndicesSize = SizeOf<uint32>(_raw.indices);
		mIndexBuffer.Create(_device,
			_init,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
			sizeof(uint32) * mIndicesSize,
			_raw.indices.data());
		
		SA_LOG(L"Static Mesh created.", Infos, SA/Render/Vulkan);
	}
	
	void StaticMesh::Destroy(const Device& _device)
	{
		mVertexBuffer.Destroy(_device);
		mIndexBuffer.Destroy(_device);

		mIndicesSize = ~uint32();
		
		SA_LOG(L"Static Mesh destroyed.", Infos, SA/Render/Vulkan);
	}


	void StaticMesh::Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos) const
	{
		const Frame& vkFrame = Cast<Frame>(_frame);

		mVertexBuffer.BindAsVertexBuffer(vkFrame.cmd);
		mIndexBuffer.BindAsIndexBuffer(vkFrame.cmd);

		vkCmdDrawIndexed(vkFrame.cmd, mIndicesSize, _infos.instanceNum, 0, 0, 0);
	}


	bool StaticMesh::operator==(const StaticMesh& _rhs) const noexcept
	{
		return mVertexBuffer == _rhs.mVertexBuffer && mIndexBuffer == _rhs.mIndexBuffer;
	}
}
