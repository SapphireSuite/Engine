// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_QUEUE_GUARD
#define SAPPHIRE_CORE_THREAD_QUEUE_GUARD

#include <queue>
#include <vector>

#include <SA/Core/Types/Variadics/Function.hpp>

#include <SA/Core/Thread/Queue/ThreadJoinMode.hpp>
#include <SA/Core/Thread/Queue/ThreadQueueWorker.hpp>
#include <SA/Core/Thread/Queue/ThreadQueueTask.hpp>

/**
*	\file ThreadQueue.hpp
* 
*	\brief ThreadQueue implementation.
*	Push task to queue, which will be executed on external thread.
* 
*	\ingroup Core_Thread
*	\{
*/


namespace Sa
{
	/// ThreadQueue class.
	class ThreadQueue
	{
		/// Current workers.
		std::vector<ThreadQueueWorker> mWorkers;

		/// Queued tasks.
		std::queue<ThreadQueueTask> mTaskQueue;

		/// Mutex for queue access.
		std::mutex mQueueMutex;

		/// Current Queue size.
		std::atomic<uint32> mQueueSize;

		/// Current processing task number.
		std::atomic<uint32> mProcessingNum;

		/// Queue running state.
		std::atomic<bool> mIsRunning = true;

		/**
		*	\brief Internal add task to queue implementation.
		* 
		*	\param[in] _task	Task to add to queue.
		*/
		void AddTask(ThreadQueueTask&& _task);

	public:
		/// Create infos struct.
		struct CreateInfos
		{
			/// Number of external thread.
			uint32 threadNum = 2u;
		};

		/**
		*	\brief Create ThreadQueue from infos.
		* 
		*	\param[in] _infos	Infos used for creation.
		*/
		void Create(const CreateInfos& _infos);

		/**
		*	\brief Join and destroy the queue.
		*/
		void Destroy();

		/**
		*	\brief Current running state.
		*	Thread Safe.
		* 
		*	\return queue running state.
		*/
		bool IsRunning() const;

		/**
		*	\brief Current queue size.
		*	Thread Safe.
		* 
		*	\return queue size.
		*/
		uint32 QueueSize() const;

		/**
		*	\brief Callback function on task has been processed.
		* 
		*	\param[in] _task	Processed task.
		*/
		void OnTaskProcessed(const ThreadQueueTask& _task);


		/**
		*	\brief Push a PackedFunction as a task to execute on an external thread.
		* 
		*	\tparam R				Function return type.
		*	\tparam Args			Function arguments type.
		*	\param[in,out] _func	PackedFunction to push.
		* 
		*	\return future handle.
		*/
		template <typename R, typename... Args>
		std::future<R> Push(PackedFunction<R, Args...>&& _func);

		/**
		*	\brief Push a static function ptr as a task to execute on an external thread.
		* 
		*	\tparam R		Function return type.
		*	\tparam Args	Function arguments type.
		*	\param _func	Function ptr to push.
		*	\param _args	Function arguments value.
		* 
		*	\return future handle.
		*/
		template <typename R, typename... Args>
		std::future<R> Push(R(*_func)(Args...), Args... _args);

		/**
		*	\brief Push a pointer to member function as a task to execute on an external thread.
		* 
		*	\tparam C		Caller type.
		*	\tparam R		Function return type.
		*	\tparam Args	Function arguments type.
		*	\param _caller	Caller value.
		*	\param _func	Member function ptr to push.
		*	\param _args	Function arguments value.
		* 
		*	\return future handle.
		*/
		template <typename C, typename R, typename... Args>
		std::future<R> Push(C* _caller, R(C::*_func)(Args...), Args... _args);

		/**
		*	\brief Pop a task from the queue.
		* 
		*	\param[out] _task	Output task value.
		* 
		*	\return true on pop success, otherwise false.
		*/
		bool Pop(ThreadQueueTask& _task);


		/**
		*	\brief Join all queued tasks.
		*	Make this thread wait until all task as been processed.
		* 
		*	\param[in] _mode	Join mode.
		*/
		void Join(ThreadJoinMode _mode = ThreadJoinMode::Complete);
	};
}

#include <SA/Core/Thread/Queue/ThreadQueue.inl>


/** \} */

#endif // GUARD
