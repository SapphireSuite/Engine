// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_QUEUE_GUARD
#define SAPPHIRE_CORE_THREAD_QUEUE_GUARD

#include <queue>
#include <vector>

#include <future>

#include <SA/Config.hpp>

#include <SA/Core/Thread/Queue/ThreadJoinMode.hpp>
#include <SA/Core/Thread/Queue/ThreadQueueWorker.hpp>
#include <SA/Core/Thread/Queue/ThreadQueueTask.hpp>

namespace Sa
{
	class ThreadQueue
	{
		std::vector<ThreadQueueWorker> mWorkers;

		std::queue<ThreadQueueTask> mTaskQueue;
		std::mutex mQueueMutex;
		std::atomic<uint32> mQueueSize;
		std::atomic<uint32> mProcessingNum;

		std::atomic<bool> mIsRunning = true;

		SA_ENGINE_API void AddTask(ThreadQueueTask&& _task);

	public:
		struct CreateInfos
		{
			uint32 threadNum = 2u;
		};

		SA_ENGINE_API void Create(const CreateInfos& _infos);
		SA_ENGINE_API void Destroy();

		bool IsRunning() const;
		uint32 QueueSize() const;

		void OnTaskProcessed(const ThreadQueueTask& _task);

		template <typename R, typename... Args>
		std::future<R> Push(R(*_func)(Args...), Args&&... _args);

		bool Pop(ThreadQueueTask& _task);

		SA_ENGINE_API void Join(ThreadJoinMode _mode = ThreadJoinMode::Complete);
	};
}

#include <SA/Core/Thread/Queue/ThreadQueue.inl>

#endif // GUARD
