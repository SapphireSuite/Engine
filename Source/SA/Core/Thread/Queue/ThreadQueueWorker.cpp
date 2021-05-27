// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Thread/Queue/ThreadQueueWorker.hpp>

#include <Core/Thread/Queue/ThreadQueue.hpp>

namespace Sa
{
	void ThreadQueueWorker::Create(ThreadQueue& _queue)
	{
		mHandle = std::thread(
			[&_queue]()
			{
				ThreadQueueTask task;

				while (_queue.IsRunning())
				{
					// Wait for queue.
					std::this_thread::yield();

					while (_queue.QueueSize() && _queue.Pop(task))
					{
						task.handle();

						_queue.OnTaskProcessed(task);
					}
				}
			}
		);
	}

	void ThreadQueueWorker::Destroy()
	{
		if (mHandle.joinable())
			mHandle.join();
	}
}
