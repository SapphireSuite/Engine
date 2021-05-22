// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_ATTACHMENT_GUARD
#define SAPPHIRE_CORE_THREAD_ATTACHMENT_GUARD

#include <thread>

#include <SA/Core/Thread/Pipeline/ThreadState.hpp>

/**
*	\file ThreadAttachment.hpp
*
*	\brief \b Thread Attachment type implementation.
*
*	\ingroup Core_Thread
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

			/// input attachment index (if any).
			uint32 inAttachIndex = uint32(-1);

			/// Main method to run.
			Function<void(ThreadState&)> main;
		};

		/// Attachment's state.
		ThreadState state;

		/**
		*	Value Constructor.
		*
		*	\param[in]	_infos		Attachment create infos.
		*/
		ThreadAttachment(CreateInfos&& _infos, std::atomic<float>& _bHasStarted, std::atomic<float>& _bIsRunning);


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
