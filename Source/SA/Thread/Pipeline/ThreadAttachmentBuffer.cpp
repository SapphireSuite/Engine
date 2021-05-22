// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Thread/Pipeline/ThreadAttachmentBuffer.hpp>

#include <Collections/Debug>

namespace Sa::Thread
{
	const void* AttachmentBuffer::Acquire()
	{
		mMutex.lock_shared();

		return mBuffer;
	}

	void AttachmentBuffer::Release()
	{
		mMutex.unlock_shared();
	}


	//void AttachmentBuffer::SwapBuffer(const void*& _buffer)
	//{
	//	SA_ASSERT(Nullptr, Thread, _buffer);

	//	mMutex.lock();

	//	std::swap(mBuffer, _buffer);

	//	mMutex.unlock();
	//}
}
