// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_MESH_MGR_GUARD
#define SAPPHIRE_RENDER_VK_MESH_MGR_GUARD

#include <forward_list>

#include <SA/Render/Vulkan/Mesh/VkBLStaticMesh.hpp>

#include <SA/Render/Vulkan/Buffers/CGPU/VkCGPUBuffer.hpp>
#include <SA/Render/Vulkan/Buffers/GPU/VkGPUBufferHeap.hpp>

#include <SA/Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorPool.hpp>
#include <SA/Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorSetLayout.hpp>

namespace Sa::Vk
{
	class MeshMgr
	{
		GPUBufferHeap mVertexHeap;
		GPUBufferHeap mIndicesHeap;

		struct Frame
		{
			// Transform storage buffer.
			CGPUBuffer transformBuffer;

			// Normal storage buffer.
			CGPUBuffer normalBuffer;
		};

		std::vector<Frame> mFrames;

		DescriptorPool mDescriptorPool;
		DescriptorSetLayout mDescriptorSetLayout;

		std::vector<DescriptorSet> mDescriptorSets;


		std::forward_list<BLStaticMesh> mStaticMeshes;

	public:
		void Create(const Device& _device, uint32 _frameNum = 3u);
		void Destroy(const Device& _device);

		BLStaticMesh* CreateStaticMesh(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw);
		void DestroyStaticMesh(const Device& _device, BLStaticMesh* _mesh);
	};
}

#endif // GUARD
