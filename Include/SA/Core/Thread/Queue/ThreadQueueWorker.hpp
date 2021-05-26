// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_QUEUE_WORKER_GUARD
#define SAPPHIRE_CORE_THREAD_QUEUE_WORKER_GUARD

#include <thread>
#include <atomic>

namespace Sa
{
	class ThreadQueue;

	class ThreadQueueWorker
	{
		std::thread mHandle;

	public:
		void Create(ThreadQueue& _queue);
		void Destroy();
	};
}

#endif // GUARD
