// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_QUEUE_TASK_GUARD
#define SAPPHIRE_CORE_THREAD_QUEUE_TASK_GUARD

#include <memory>
#include <future>

namespace Sa
{
	namespace Intl
	{
		class ThreadPromiseBase
		{
		public:
			virtual ~ThreadPromiseBase() = default;
		};

		template <typename T>
		class ThreadPromise : public ThreadPromiseBase
		{
		public:
			std::promise<T> handle;
		};
	}

	class ThreadQueueTask
	{
	public:
		std::packaged_task<void()> handle;
		std::unique_ptr<Intl::ThreadPromiseBase> promise;

		template <typename R>
		static ThreadQueueTask Make(std::promise<R>*& _hPromise);
	};
}

#include <SA/Core/Thread/Queue/ThreadQueueTask.inl>

#endif // GUARD
