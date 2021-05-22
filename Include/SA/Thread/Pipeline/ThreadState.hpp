// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_STATE_GUARD
#define SAPPHIRE_CORE_THREAD_STATE_GUARD

#include <atomic>
#include <shared_mutex>

#include <SA/Core/Types/Variadics/Event.hpp>

/**
*	\file ThreadState.hpp
*
*	\brief \b Thread Attachment \b State type.
*
*	\ingroup Core_Thread
*	\{
*/


namespace Sa
{
	class ThreadPipeline;

	/**
	*	\brief Thread State class.
	* 
	*	State of a current attachment.
	*/
	class ThreadState
	{
//{ Structs

	public:
		/// Methods used for query.
		enum class QueryMode
		{
			None,

			// Copy data using provided copyBuffer callback.
			Copy = 1,

			// Move data (using swap).
			Move,
		};

		/// Attachment input state.
		enum class InputState
		{
			/// Yield thread and wait for input attachment submit.
			WaitForInSubmit = 1,

			/// Use self output as new input if no new input has been submitted.
			SelfSubmit,
		};

		/// Create infos struct.
		struct CreateInfos
		{
			/// Update frequency.
			float frequency = 1.0f / 60.0f;


			/// User defined input fetching method (if no input attachment).
			Function<bool(void*& _inBuffer)> fetchInput;

			/// User defined copy buffer method.
			Function<void(const void*, void*)> copyBuffer;

			/// Callback reset output buffer before use.
			Function<void(void*)> resetBuffer;


			/// Query output method.
			QueryMode queryMode = QueryMode::Copy;

			/// Input's fetching method.
			InputState inputState = InputState::WaitForInSubmit;
		};

//}

	private:
		/// current running time.
		std::atomic<float> mCurrTime = 0.0f;


//{ Triple Buffering

		/// Triple-buffering: Input buffer.
		void* mInBuffer = nullptr;

		/// Triple-buffering: current output buffer.
		void* mCurrBuffer = nullptr;

		/// Triple-buffering: last submitted output buffer.
		void* mOutBuffer = nullptr;

		/// Output buffer mutex.
		std::shared_mutex mOutputMutex;

		/**
		*	\brief User defined copy buffer method.
		*
		*	Must be provided if:
		*	- queryMode = QueryMode::Copy
		*	- multiple attachments use same input attachment (or at least one + SelfSubmit).
		*/
		Function<void(const void*, void*)> mCopyBuffer;

		/// Callback reset output buffer before use.
		Function<void(void*)> mResetBuffer;


		void SwapBuffers();

//}


//{ Input/Output

		/// Called on new output.
		Event<void()> mOnOutput;


		/// Fetch input method. Called on request new inputs.
		Function<bool(void*&)> mFetchInput;

		/// Fetch new input using defined input attachment method.
		bool FetchInput();


		/// Thread state of input attachment (if any).
		ThreadState* mInAttach = nullptr;

		/// Atomic bool should fetch new input from input attachment (if any).
		std::atomic<bool> mShouldFetchInAttach = true;

		/**
		*	Set ShouldFetchInAttach to true.
		*	Callback method called from input attachment event.
		*/
		void SetShouldFetchInAttach();

		/**
		*	\brief Fetch new input buffer from input attachment.
		*
		*	\param[out] _inBuffer	ptr to input buffer.
		*
		*	\returns true on fetching success.
		*/
		bool FetchInAttachment(void*& _inBuffer);

		/**
		*	Query input attachment's output.
		* 
		*	\param[out] _dst			output ptr.
		*/
		void QueryOutput(void*& _dst, QueryMode _overrideMode = QueryMode::None);
//}



		/// Currently running pipeline state ref.
		std::atomic<float>& bIsRunning;


		/// Yield current thread until next frame (depending on frequency).
		void Yield();

	public:
		/// Update frequency.
		const float frequency = 1.0f / 60.0f;

		/// Query output method.
		const QueryMode queryMode = QueryMode::Copy;

		/// Input's fetching method.
		const InputState inputState = InputState::WaitForInSubmit;


		/**
		*	\brief Value constructor.
		*
		*	\param[in] _infos		State create infos.
		*	\param[in] _bIsRunning	Atomic running from ThreadPipeline.
		*/
		ThreadState(CreateInfos&& _infos, std::atomic<float>& _bIsRunning);

		/**
		*	\brief Default Move constructor.
		* 
		*	\param[in] _other	moved object.
		* 
		*	Should never be used.
		*	Requiered for std::vector compilation but never used.
		*/
		ThreadState(ThreadState&& _other) noexcept;


		/**
		*	\brief Init input attachment state.
		*
		*	\param[in]	_inAttach	State of input attachment.
		*/
		void InitInputAttachment(ThreadState& _inAttach);

//{ Buffers

		/**
		*	\brief Typed getter of input buffer.
		* 
		*	\tparam T	Type to cast in.
		* 
		*	\returns Type-casted input buffer.
		*/
		template <typename T>
		const T* GetInputBuffer() const;

		/**
		*	\brief Typed getter of output buffer.
		* 
		*	\tparam T	Type to cast in.
		* 
		*	\returns Type-casted output buffer.
		*/
		template <typename T>
		T* GetOutputBuffer() const;


		/**
		*	\brief Create triple buffering using user defined functor.
		* 
		*	\tparam InFuncT					Create-input-buffer Functor type.
		*	\tparam OutFuncT				Create-output-buffer Functor type.
		*	\param[in] _inBuffFunctor		User defined create input buffer functor.
		*	\param[in] _outBuffFunctor		User defined create output buffer functor.
		*/
		template <typename InFuncT, typename OutFuncT>
		void CreateBuffers(const InFuncT& _inBuffFunctor, const OutFuncT& _outBuffFunctor);

		/**
		*	\brief Destroy triple buffering using user defined functor.
		* 
		*	\tparam InFuncT					Create-input-buffer Functor type.
		*	\tparam OutFuncT				Create-output-buffer Functor type.
		*	\param[in] _inBuffFunctor		User defined destroy input buffer functor.
		*	\param[in] _outBuffFunctor		User defined destroy output buffer functor.
		*/
		template <typename InFuncT, typename OutFuncT>
		void DestroyBuffers(const InFuncT& _inBuffFunctor, const OutFuncT& _outBuffFunctor);

//}

		/**
		*	Submit changes applied to current output buffer.
		*	Must be called on each attachment's frame.
		* 
		*	\returns Should thread keep running.
		*/
		SA_ENGINE_API bool Submit();

		/**
		*	\brief Update state from time (called by pipeline).
		* 
		*	\param[in] _deltaTime	 delta time.
		*/
		void Update(float _deltaTime);
	};
}


/** \} */

#include <SA/Thread/Pipeline/ThreadState.inl>

#endif // GUARD
