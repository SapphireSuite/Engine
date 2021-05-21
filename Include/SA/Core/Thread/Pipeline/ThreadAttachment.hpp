// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_ATTACHMENT_GUARD
#define SAPPHIRE_CORE_THREAD_ATTACHMENT_GUARD

#include <thread>

#include <SA/Core/Thread/Pipeline/ThreadState.hpp>

/**
*	\file ThreadAttachment.hpp
*
*	\brief \b Definition of Sapphire's Suite \b Thread Attachment type.
*
*	\ingroup Thread
*	\{
*/


namespace Sa
{
	/**
	*	\brief Thread Attachment class.
	* 
	*	Attachments are used to create a Pipeline.
	*/
	class ThreadAttachment
	{
		/// Thread handle.
		std::thread mHandle;

	public:
		/// Create infos struct.
		struct CreateInfos
		{
			/// State create infos.
			ThreadState::CreateInfos stateInfos;

			/// Main method to run.
			void (*method)(ThreadState&) = nullptr;
		};

		/// State of attachment.
		ThreadState state;

		/**
		*	Value Constructor.
		*
		*	\param[in]	_infos		Attachment create infos.
		*	\param[in] _bIsRunning	Atomic running from ThreadPipeline.
		*/
		ThreadAttachment(const CreateInfos& _infos, std::atomic<float>& _bIsRunning);

		/**
		*	Update the attachment from time.
		* 
		*	\param[in] _deltaTime delta time
		*/
		void Update(float _deltaTime);

		/// Join attachment.
		void Join();
	};
}


/** \} */

#endif // GUARD
