// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_BL_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_VK_BL_STATIC_MESH_GUARD

#include <SA/Render/Base/Mesh/AStaticMesh.hpp>

#include <SA/Render/Vulkan/Buffers/VkBufferHeap.hpp>

namespace Sa::Vk
{
	class Device;
	class ResourceInitializer;
	class GPUBufferHeap;

	/**
	*	Bindless implementation of Static Mesh.
	*	Bindless required the use of BufferHeap instead of Buffer.
	*/
	class BLStaticMesh : public AStaticMesh
	{
		const BufferHeap::MetaData* mVertexMeta = nullptr;
		const BufferHeap::MetaData* mIndexMeta = nullptr;

		uint32 mIndicesSize = ~uint32();

	public:
		void Create(const Device& _device,
			ResourceInitializer& _init,
			GPUBufferHeap& _meshVertexHeap,
			GPUBufferHeap& _meshIndicesHeap,
			const RawMesh& _raw);
		void Destroy(const Device& _device, GPUBufferHeap& _meshVertexHeap, GPUBufferHeap& _meshIndicesHeap);

		void Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos = MeshDrawInfos()) const override final;

		bool operator==(const BLStaticMesh& _rhs) const noexcept;
	};
}

#endif // GUARD
