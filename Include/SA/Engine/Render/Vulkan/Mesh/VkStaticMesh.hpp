// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_VK_STATIC_MESH_GUARD
#define SAPPHIRE_VK_STATIC_MESH_GUARD

#include <SA/Engine/Render/Base/Mesh/AStaticMesh.hpp>

#include <SA/Engine/Render/Vulkan/Buffers/ObjectBuffer/GPU/VkGPUBuffer.hpp>

namespace SA::VK
{
	class Device;
	class ResourceInitializer;

	class StaticMesh : public AStaticMesh
	{
		GPUBuffer mVertexBuffer;
		GPUBuffer mIndexBuffer;

		uint32_t mIndicesSize = ~uint32_t();

		using AStaticMesh::Create; // overloaded.
        using AStaticMesh::Destroy; // overloaded.

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw);
		void Destroy(const Device& _device);

		void Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos = MeshDrawInfos()) const override final;
	};
}

#endif // GUARD
