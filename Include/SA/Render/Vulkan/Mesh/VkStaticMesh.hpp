// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD

#include <SA/Render/Base/Mesh/AStaticMesh.hpp>

#include <SA/Render/Vulkan/Buffers/VkGPUBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class StaticMesh : public AStaticMesh
	{
		GPUBuffer mVertexBuffer;
		GPUBuffer mIndexBuffer;

		uint32 mIndicesSize = ~uint32();

	public:
		void Create(ARenderResourceInitializer* _init, const RawMesh& _raw) override final;
		void Destroy(const ARenderDevice* _device) override final;

		void Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos = MeshDrawInfos()) const override final;
	};
}

#endif

#endif // GUARD
