// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_QUEUE_TASK_GUARD
#define SAPPHIRE_CORE_THREAD_QUEUE_TASK_GUARD

#include <memory>
#include <future>

/**
*	\file ThreadQueueTask.hpp
* 
*	\brief Task implementation for ThreadQueue.
* 
*	\ingroup Core_Thread
*	\{
*/

namespace Sa
{
	/// \cond Internal

	namespace Intl
	{
		/// Thread promise base class (non-typed).
		class ThreadPromiseBase
		{
		public:
			virtual ~ThreadPromiseBase() = default;
		};

		/**
		*	\brief Typed thread promise class.
		*/
		template <typename T>
		class ThreadPromise : public ThreadPromiseBase
		{
		public:
			/// Handled promise.
			std::promise<T> handle;
		};
	}

	/// \endcond

	/// ThreadQueue Task class implementation.
	class ThreadQueueTask
	{
	public:
		/// Handled task function.
		std::packaged_task<void()> handle;

		/// Promise abstract handle.
		std::unique_ptr<Intl::ThreadPromiseBase> promise;

		/**
		*	\brief Create a ThreadQueueTask and fill typed promise handle.
		* 
		*	\tparam R				Promise (return) type.
		*	\param[out] _hPromise	Handle typed promise to fill.
		* 
		*	\return Created ThreadQueueTask.
		*/
		template <typename R>
		static ThreadQueueTask Make(std::promise<R>*& _hPromise);
	};
}

#include <SA/Core/Thread/Queue/ThreadQueueTask.inl>


/** \} */

#endif // GUARD
