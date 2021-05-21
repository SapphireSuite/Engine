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
		/// current running time.
		std::atomic<float> mCurrTime = 0.0f;

		/// Output buffer mutex.
		std::shared_mutex mOutputMutex;


		/// Pointer for user.
		void* const mUserData = nullptr;

		/// Triple-buffering: Input buffer.
		void* mInBuffer = nullptr;

		/// Triple-buffering: current output buffer.
		void* mCurrBuffer = nullptr;

		/// Triple-buffering: last submitted output buffer.
		void* mOutBuffer = nullptr;


		/// Thread state of input attachment (if any).
		ThreadState* mInAttach = nullptr;

		/// Atomic bool should fetch new input from input attachment (if any)
		std::atomic<bool> mShouldFetchInAttach = true;


		/// Called on request new inputs.
		bool (*mFetchInput)(void*& _inBuffer, void* _userData) = nullptr;

		/// Called on new output.
		Event<void(void*, void*)> mOnOutput;

		/// Callback: copy buffer.
		void (*mCopyBuffer)(const void* _src, void* _dst) = nullptr;

		/// Callback reset output buffer before use.
		void (*mResetBuffer)(void* _outBuffer, void* _userData) = nullptr;

		/// Currently running state ref.
		std::atomic<float>& bIsRunning;

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

			/// Use self output as new input if no input submit.
			SelfSubmit,
		};

		/// Create infos struct.
		struct CreateInfos
		{
			/// Update frequency.
			float frequency = 1.0f / 60.0f;

			/// Pointer for user.
			void* userData = nullptr;


			/// User defined input fetching method.
			bool (*fetchInput)(void*&, void*) = nullptr;

			/// User callback on new output submitted.
			void (*onOutput)(void*, void*) = nullptr;
			
			/// User defined copy buffer method. Must be provided if queryMode = QueryMode::Copy.
			void (*copyBuffer)(const void*, void*) = nullptr;

			/// User defined reset buffer method.
			void (*resetBuffer)(void*, void*) = nullptr;

			/// input attachment index (if any).
			unsigned int inAttachIndex = static_cast<unsigned int>(-1);


			/// Query output method.
			QueryMode queryMode = QueryMode::Copy;
			
			/// Input's fetching method.
			InputState inputState = InputState::WaitForInSubmit;
		};


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
		ThreadState(const CreateInfos& _infos, std::atomic<float>& _bIsRunning);

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
		*	\brief Typed getter of registered user data.
		* 
		*	\tparam T	Type to cast in.
		* 
		*	\returns Type-casted user data.
		*/
		template <typename T>
		T* GetUserData() { return reinterpret_cast<T*>(mUserData); }

		/**
		*	\brief Typed getter of input buffer.
		* 
		*	\tparam T	Type to cast in.
		* 
		*	\returns Type-casted input buffer.
		*/
		template <typename T>
		const T* GetInputBuffer() { return reinterpret_cast<const T*>(mInBuffer); }

		/**
		*	\brief Typed getter of output buffer.
		* 
		*	\tparam T	Type to cast in.
		* 
		*	\returns Type-casted output buffer.
		*/
		template <typename T>
		T* GetOutputBuffer() { return reinterpret_cast<T*>(mCurrBuffer); }


		/**
		*	\brief Getter of pipeline running state.
		* 
		*	\returns pipeline is running state
		*/
		SA_ENGINE_API bool IsRunning() const;


		/**
		*	\brief Init input attachment state.
		* 
		*	\param[in]	_inAttach	State of input attachment.
		*/
		void InitInputAttachment(ThreadState& _inAttach);

		/**
		*	\brief Create triple buffering.
		* 
		*	\param[in] _inBuff		input buffer.
		*	\param[in] _outBuff1	output buffer 1.
		*	\param[in] _outBuff2	output buffer 2.
		*/
		SA_ENGINE_API void CreateBuffers(void* _inBuff, void* _outBuff1 = nullptr, void* _outBuff2 = nullptr);

		/**
		*	\brief Destroy triple buffering.
		*
		*	\param[in] _destroyInBuff	User defined destroy method of input buffer.
		*	\param[in] _destroyOutBuff	User defined destroy method of output buffer.
		*/
		SA_ENGINE_API void DestroyBuffers(void (*_destroyInBuff)(void*) = nullptr, void (*_destroyOutBuff)(void*) = nullptr);


		/**
		*	Update state from time.
		*
		*	\param[in] _deltaTime	 delta time.
		*/
		void Update(float _deltaTime);

		/**
		*	Submit changes applied to current output buffer.
		*	Must be called on each attachment's frame.
		*/
		SA_ENGINE_API void Submit();

	private:
		/// Yield current thread until next frame (depending on frequency).
		void Yield();

		/// Fetch new input using defined input attachment method.
		void FetchInput();

		/**
		*	Set ShouldFetchInAttach to true.
		*	Callback method called from input attachment event.
		* 
		*	\param[in] _outBuff		unused
		*	\param[in] _userData	unused
		*/
		void SetShouldFetchInAttach(void* _outBuff, void* _userData);

		/**
		*	\brief Fetch new input buffer from input attachment.
		* 
		*	\param[out] _inBuffer	ptr to input buffer.
		*	\param[in]	_userData	user data.
		* 
		*	\returns true on fetching success.
		*/
		bool FetchInAttachment(void*& _inBuffer, void* _userData);

		/**
		*	Query input attachment's output.
		* 
		*	\param[out] _dst			output ptr.
		*	\param[in]	_overrideMode	Additional override query mode.
		*	\param[in] _bLock			Additional should lock.
		*/
		void QueryOutput(void*& _dst, QueryMode _overrideMode = QueryMode::None, bool _bLock = true);
	};
}


/** \} */

#endif // GUARD
