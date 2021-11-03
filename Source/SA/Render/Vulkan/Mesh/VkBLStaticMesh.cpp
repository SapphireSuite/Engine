// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Mesh/VkBLStaticMesh.hpp>

#include <Core/Algorithms/Cast.hpp>
#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/VkFrame.hpp>
#include <Render/Vulkan/VkResourceInitializer.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

#include <Render/Vulkan/Buffers/GPU/VkGPUBufferHeap.hpp>

namespace Sa::Vk
{
	void BLStaticMesh::Create(const Device& _device,
		ResourceInitializer& _init,
		GPUBufferHeap& _meshVertexHeap,
		GPUBufferHeap& _meshIndicesHeap,
		const RawMesh& _raw)
	{
		mLayout = _raw.GetLayout();

		mIndicesSize = SizeOf<uint32>(_raw.indices);

		mVertexMeta = _meshVertexHeap.Allocate(_device, _init, _raw.vertices.data(), SizeOf(_raw.vertices));
		mIndexMeta = _meshIndicesHeap.Allocate(_device, _init, _raw.indices.data(), sizeof(uint32) * mIndicesSize);

		SA_LOG(L"Bindless Static Mesh created.", Infos, SA/Render/Vulkan);
	}
	
	void BLStaticMesh::Destroy(const Device& _device, GPUBufferHeap& _meshVertexHeap, GPUBufferHeap& _meshIndicesHeap)
	{
		mIndicesSize = ~uint32();

		_meshVertexHeap.Free(mVertexMeta);
		_meshIndicesHeap.Free(mIndexMeta);
		
		mVertexMeta = nullptr;
		mIndexMeta = nullptr;

		SA_LOG(L"Bindless Static Mesh destroyed.", Infos, SA/Render/Vulkan);
	}


	void BLStaticMesh::Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos) const
	{
		const Frame& vkFrame = Cast<Frame>(_frame);

		vkCmdDrawIndexed(vkFrame.cmd, mIndicesSize, _infos.instanceNum, mIndexMeta->offset, mVertexMeta->offset, 0);
	}


	bool BLStaticMesh::operator==(const BLStaticMesh& _rhs) const noexcept
	{
		return mVertexMeta == _rhs.mVertexMeta && mIndexMeta == _rhs.mIndexMeta;
	}
}
