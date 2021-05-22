// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_THREAD_ATTACHMENT_BUFFER_GUARD
#define SAPPHIRE_THREAD_ATTACHMENT_BUFFER_GUARD

#include <shared_mutex>

namespace Sa::Thread
{
	class AttachmentBuffer
	{
		const void* mBuffer = nullptr;

		std::shared_mutex mMutex;

	public:
		const void* Acquire();
		void Release();

		//void SwapBuffer(const void*& _buffer);
	};
}

#endif // GUARD
