// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Buffers/RenderBufferType.hpp>

#include <Collections/Debug>

namespace Sa
{
#if SA_VULKAN

	namespace Vk
	{
		VkBufferUsageFlagBits API_GetBufferUsage(RenderBufferType _type)
		{
			switch (_type)
			{
				case RenderBufferType::Uniform:
					return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
				case RenderBufferType::Storage:
					return VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
				case RenderBufferType::Vertex:
					return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
				case RenderBufferType::Index:
					return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
				case RenderBufferType::TransferSRC:
					return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
				case RenderBufferType::TransferDST:
					return VK_BUFFER_USAGE_TRANSFER_DST_BIT;
				default:
				{
					SA_LOG(L"Buffer type usage ["<< _type << L"]not supported yet!", Error, SA/Render/Vulkan);
					return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
				}
			}
		}
	}

#endif
}
