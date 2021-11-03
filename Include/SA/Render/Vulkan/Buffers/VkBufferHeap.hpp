// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_BUFFER_HEAP_GUARD
#define SAPPHIRE_RENDER_VK_BUFFER_HEAP_GUARD

#include <list>

#include <SA/Render/Vulkan/Buffers/VkBuffer.hpp>

namespace Sa::Vk
{
	class BufferHeap : public Buffer
	{
	protected:

		VkBufferUsageFlags mUsage = 0;
		VkMemoryPropertyFlags mProperties = 0;

//{ Meta

		struct MetaData
		{
			uint64 size = uint64(-1);
			uint64 offset = 0u;

			MetaData* prev = nullptr;
			MetaData* next = nullptr;

			bool bFreeBlock = true;

			bool operator<(const MetaData& _rhs) const;
		};

		MetaData* mTail = nullptr;
		std::list<MetaData*> mBlocks;

		
		MetaData* AllocateMeta(const Device& _device, uint64 _size);


		/**
		*	Insert metadata next current.
		* 
		*	\param[in] _curr		Current metadata.
		*	\param[in] _newMeta		New metadata to insert.
		*/
		void InsertNext(MetaData* _curr, MetaData* _newMeta);

		/**
		*	Fusion prev and meta block if possible.
		*
		*	\param[in] _prev		Previous block.
		*	\param[in, out] _meta	Current block. Output as new fusionned block if success.
		*
		*	\return Has fusionned blocks.
		*/
		bool FusionBlock(MetaData* _prev, MetaData*& _meta);


		void ClearMeta();

//}

		MetaData* Realloc(const Device& _device, uint64 _newCapacity);

		virtual void ReallocBuffer(const Device& _device, uint64 _newCapacity) = 0;

	public:
		void Create(const Device& _device,
			uint64 _size, VkBufferUsageFlags _usage,
			VkMemoryPropertyFlags _properties) override;
		void Destroy(const Device& _device) override;

		//uint64 Allocate(const Device& _device, void* _data, uint64 _size);
		void Free(const Device& _device, uint64 _ID);
	};
}

#endif // GUARD
