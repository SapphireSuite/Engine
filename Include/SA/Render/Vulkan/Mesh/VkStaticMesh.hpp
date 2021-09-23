// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD

#include <SA/Render/Base/Mesh/AMesh.hpp>

#include <SA/Render/Vulkan/Buffers/VkDeviceBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class StaticMesh : public AMesh
	{
		DeviceBuffer mVertexBuffer;
		DeviceBuffer mIndexBuffer;

		uint32 mIndicesSize = ~uint32();

	public:
		void Create(const Device& _device, CommandBuffer& _cmd, ResourceHolder& _resHold, const RawMesh& _raw);
		void Destroy(const Device& _device);

		void Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos = MeshDrawInfos()) const override final;
	};
}

#endif

#endif // GUARD
