// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_PIPELINE_GUARD
#define SAPPHIRE_CORE_THREAD_PIPELINE_GUARD

#include <vector>

#include <SA/Core/Thread/Pipeline/ThreadAttachment.hpp>

/**
*	\file ThreadPipeline.hpp
*
*	\brief \b Definition of Sapphire's Suite \b Thread Pipeline type.
*
*	\ingroup Thread
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
		std::atomic<float> bIsRunning = false;

	public:
		/// Create infos struct.
		struct CreateInfos
		{
			/**
			*	Attachments' create infos.
			*	One attachment will be created for each infos.
			*/
			std::vector<ThreadAttachment::CreateInfos> attachInfos;

			/// Instantly start upon creation. Manually call Start() instead.
			bool bStartOnCreate = false;
		};

		/// Default constructor.
		ThreadPipeline() = default;

		/**
		*	\brief In-Constructor creation.
		* 
		*	\param[in] _infos	Create infos.
		*/
		ThreadPipeline(const CreateInfos& _infos);

		/// Deleted move constructor.
		ThreadPipeline(ThreadPipeline&&) = delete;

		/// Deleted copy constructor.
		ThreadPipeline(const ThreadPipeline&) = delete;

		/**
		*	\brief getter of attachment by index.
		*	Attachment index is defined by order in create infos.
		* 
		*	\param[in] _index	Index of attachment.
		* 
		*	\returns attachment at index.
		*/
		ThreadAttachment& GetAttachment(unsigned int _index);

		/**
		*	\brief const getter of attachment by index.
		*	Attachment index is defined by order in create infos.
		* 
		*	\param[in] _index	Index of attachment.
		* 
		*	\returns attachment at index.
		*/
		const ThreadAttachment& GetAttachment(unsigned int _index) const;

		/**
		*	\brief Create pipeline from infos.
		* 
		*	\param[in] _infos	creation infos.
		*/
		SA_ENGINE_API void Create(const CreateInfos& _infos);

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
	};
}


/** \} */

#endif // GUARD
