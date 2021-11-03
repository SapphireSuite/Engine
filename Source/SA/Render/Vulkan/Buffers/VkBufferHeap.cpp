// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkBufferHeap.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
	#define SA_VK_DEVICE_HEAP_MIN_BLOCK_SIZE 1024

	void BufferHeap::Create(const Device& _device,
		uint64 _size, VkBufferUsageFlags _usage,
		VkMemoryPropertyFlags _properties)
	{
		// Required flag for Realloc.
		_usage |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

		mUsage = _usage;

		Buffer::Create(_device, _size, _usage, _properties);

		mTail = new MetaData{ _size };
		mBlocks.push_back(mTail);
	}

	void BufferHeap::Destroy(const Device& _device)
	{
		mUsage = 0;

		ClearMeta();

		Buffer::Destroy(_device);
	}


//{ Allocs

	void BufferHeap::Free(uint64 _ID)
	{
		MetaData* meta = reinterpret_cast<MetaData*>(_ID);

		meta->bFreeBlock = true;

		bool bFusion = false;

		bFusion |= FusionBlock(meta->prev, meta);
		bFusion |= FusionBlock(meta, meta->next);

		if (bFusion)
			mBlocks.sort();
	}

	BufferHeap::MetaData* BufferHeap::Realloc(const Device& _device, uint64 _newCapacity, ResourceInitializer* _init)
	{
		const uint64 prevSize = mDeviceSize;

		ReallocBuffer(_device, _newCapacity, _init);
		
		if (mTail->bFreeBlock)
			mTail->size += _newCapacity - prevSize; // Add size to tail.
		else
		{
			// Insert new meta with new free size.

			MetaData* const newTail = new MetaData{ _newCapacity - prevSize };

			InsertNext(mTail, newTail);
			mBlocks.push_back(newTail);
		}

		// Optimization: will be sorted later.
		//mBlocks.sort();

		return mTail;
	}

//}


//{ Meta

	bool BufferHeap::MetaData::operator<(const MetaData& _rhs) const
	{
		return size < _rhs.size;
	}


	BufferHeap::MetaData* BufferHeap::AllocateMeta(const Device& _device, uint64 _size, ResourceInitializer* _init)
	{
		bool bShouldSort = false;
		MetaData* meta = nullptr;

		for (auto metaIt : mBlocks)
		{
			// Find first suitable meta (sorted by size).
			if (metaIt->bFreeBlock && _size < metaIt->size)
			{
				meta = metaIt;
				break;
			}
		}


		// Not enough space left: Realloc.
		if (meta == nullptr)
		{
			uint64 newCapacity = mDeviceSize + _size;

			if (mTail->bFreeBlock)
				newCapacity -= mTail->size; //Embed free tail size.

			meta = Realloc(_device, newCapacity, _init);

			bShouldSort = true;
		}


		// Split block.
		{
			const uint64 splitSize = meta->size - _size;

			if (splitSize > SA_VK_DEVICE_HEAP_MIN_BLOCK_SIZE)
			{
				meta->size = _size;

				MetaData* const newMeta = new MetaData{ splitSize, meta->offset + _size };

				InsertNext(meta, newMeta);

				mBlocks.push_back(newMeta);

				bShouldSort = true;
			}
		}


		if(bShouldSort)
			mBlocks.sort();


		meta->bFreeBlock = false;

		return meta;
	}


	void BufferHeap::InsertNext(MetaData* _curr, MetaData* _newMeta)
	{
		_newMeta->prev = _curr;
		_newMeta->next = _curr->next;

		if (_newMeta->next)
			_newMeta->next->prev = _newMeta;
		else
			mTail = _newMeta;

		_curr->next = _newMeta;
	}

	bool BufferHeap::FusionBlock(MetaData* _prev, MetaData*& _meta)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _meta);
		SA_ASSERT(Default, SA/Render/Vulkan, _prev == _meta->prev, L"Arguments invalid! prev is not meta->prev!");

		if (_prev && _prev->bFreeBlock)
		{
			_prev->size += _meta->size;
			_prev->next = _meta->next;


			if (_meta->next)
				_meta->next->prev = _prev;
			else
				mTail = _prev;


			mBlocks.remove(_meta);

			// Optimization: will be sorted later.
			//mBlocks.sort();


			delete _meta;
			_meta = _prev;

			return true;
		}

		return false;
	}


	void BufferHeap::ClearMeta()
	{
		for (auto meta : mBlocks)
			delete meta;

		mBlocks.clear();

		mTail = nullptr;
	}

//}
}
