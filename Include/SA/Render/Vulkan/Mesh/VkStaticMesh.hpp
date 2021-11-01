// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD

#include <SA/Render/Base/Mesh/AStaticMesh.hpp>

#include <SA/Render/Vulkan/Buffers/VkGPUBuffer.hpp>

namespace Sa::Vk
{
	class Device;
	class ResourceInitializer;

	class StaticMesh : public AStaticMesh
	{
		GPUBuffer mVertexBuffer;
		GPUBuffer mIndexBuffer;

		uint32 mIndicesSize = ~uint32();

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw);
		void Destroy(const Device& _device);

		void Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos = MeshDrawInfos()) const override final;

		bool operator==(const StaticMesh& _rhs) const noexcept;
	};
}

#endif // GUARD
