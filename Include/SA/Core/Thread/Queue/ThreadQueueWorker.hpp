// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_QUEUE_WORKER_GUARD
#define SAPPHIRE_CORE_THREAD_QUEUE_WORKER_GUARD

#include <thread>
#include <atomic>

/**
*	\file ThreadQueueWorker.hpp
* 
*	\brief Thread Worker implementation for ThreadQueue.
* 
*	\ingroup Core_Thread
*	\{
*/


namespace Sa
{
	class ThreadQueue;

	/// Thread queue worker class.
	class ThreadQueueWorker
	{
		/// Handled thread.
		std::thread mHandle;

	public:
		/**
		*	\brief Create Worker with associated queue.
		* 
		*	\param[in] _queue	Associated queue.
		*/
		void Create(ThreadQueue& _queue);

		/**
		*	\brief End and destroy worker.
		*/
		void Destroy();
	};
}


/** \} */

#endif // GUARD
