// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_PIPELINE_GUARD
#define SAPPHIRE_CORE_THREAD_PIPELINE_GUARD

#include <vector>

#include <SA/Core/Thread/Pipeline/ThreadAttachment.hpp>

/**
*	\file ThreadPipeline.hpp
*
*	\brief \b Thread Pipeline type implementation.
*
*	\ingroup Core_Thread
*	\{
*/


namespace Sa
{
	/**
	*	\brief Thread Pipeline class.
	* 
	*	Create multithread pipeline.
	*/
	class ThreadPipeline
	{
		/// Attachments.
		std::vector<ThreadAttachment> mThAttachments;

		/// Currently running state.
		std::atomic<float> bIsRunning = true;

		/// Threads started running.
		std::atomic<float> bHasStarted = false;

	public:
		/// Create infos struct.
		struct CreateInfos
		{
			/**
			*	Attachments' create infos.
			*	One attachment will be created for each infos.
			*/
			std::vector<ThreadAttachment::CreateInfos> attachInfos;
		};

//{ Constructors

		/// Default constructor.
		ThreadPipeline() = default;

		/// Deleted move constructor.
		ThreadPipeline(ThreadPipeline&&) = delete;

		/// Deleted copy constructor.
		ThreadPipeline(const ThreadPipeline&) = delete;

//}

//{ Methods

		/**
		*	\brief getter of attachment by index.
		*	Attachment index is defined by order in create infos.
		*
		*	\param[in] _index	Index of attachment.
		*
		*	\returns attachment at index.
		*/
		ThreadAttachment& GetAttachment(uint32 _index);


		/**
		*	\brief Create pipeline from infos.
		*
		*	\param[in] _infos	creation infos.
		*/
		SA_ENGINE_API void Create(CreateInfos&& _infos);

		/// Destroy the created pipeline.
		SA_ENGINE_API void Destroy();


		/**
		*	Start running the pipeline.
		*	Only useful if bStartOnCreate = false in CreateInfos.
		*/
		SA_ENGINE_API void Start();

		/**
		*	Update pipeline from time.
		*
		*	\param[in] _deltaTime	delta time.
		*/
		SA_ENGINE_API void Update(float _deltaTime);

		/**
		*	End the running pipeline.
		*	Stop the running pipeline and join all attached threads.
		*/
		SA_ENGINE_API void End();
//}
	};
}


/** \} */

#endif // GUARD
