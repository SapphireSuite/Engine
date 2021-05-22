// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <cmath>

#include <Thread/Pipeline/ThreadState.hpp>

namespace Sa
{
	ThreadState::ThreadState(CreateInfos&& _infos, std::atomic<float>& _bIsRunning) :
		mCopyBuffer{ std::move(_infos.copyBuffer) },
		mResetBuffer{ std::move(_infos.resetBuffer) },
		mFetchInput{ std::move(_infos.fetchInput) },
		bIsRunning{ _bIsRunning },
		frequency{ _infos.frequency },
		queryMode{ _infos.queryMode },
		inputState{ _infos.inputState }
	{
	}

	// Requiered for std::vector compilation but never used.
	ThreadState::ThreadState(ThreadState&& _other) noexcept :
		bIsRunning{ _other.bIsRunning }
	{
	}


//{ Input Attachment

	void ThreadState::InitInputAttachment(ThreadState& _inAttach)
	{
		mInAttach = &_inAttach;

		// This fetching method.
		mFetchInput.Set(this, &ThreadState::FetchInAttachment);

		_inAttach.mOnOutput.Add(this, &ThreadState::SetShouldFetchInAttach);
	}

	void ThreadState::SetShouldFetchInAttach()
	{
		mShouldFetchInAttach = true;
	}

	bool ThreadState::FetchInput()
	{
		bool bSuccess = false;

		switch (inputState)
		{
			case InputState::WaitForInSubmit:
			{
				bSuccess = mFetchInput(mInBuffer);

				// Wait for query new input success.
				while (!bSuccess && bIsRunning)
				{
					std::this_thread::yield();
					bSuccess = mFetchInput(mInBuffer);
				}

				break;
			}
			case InputState::SelfSubmit:
			{
				// Query new input failed.
				if (!mFetchInput(mInBuffer))
				{
					// Use self output as new input (force copy).
					QueryOutput(mInBuffer, QueryMode::Copy);
				}
				
				bSuccess = true;

				break;
			}
			default:
			{
				SA_LOG(L"InputState [" << inputState << L"] not supported yet!", Error, Thread);
				break;
			}
		}

		return bSuccess;
	}

	bool ThreadState::FetchInAttachment(void*& _inBuffer)
	{
		if (!mShouldFetchInAttach)
			return false;

		mInAttach->QueryOutput(_inBuffer);

		mShouldFetchInAttach = false;

		return true;
	}


	void ThreadState::QueryOutput(void*& _dst, QueryMode _overrideMode)
	{
		QueryMode qMode = _overrideMode == QueryMode::None ? queryMode : _overrideMode;

		switch (qMode)
		{
			case QueryMode::Copy:
			{
				SA_ERROR(mCopyBuffer, Thread, L"Copy buffer method must be provided!");

				mOutputMutex.lock_shared();

				mCopyBuffer(mOutBuffer, _dst);

				mOutputMutex.unlock_shared();

				break;
			}
			case QueryMode::Move:
			{
				mOutputMutex.lock();

				std::swap(mOutBuffer, _dst);

				mOutputMutex.unlock();

				break;
			}
			default:
			{
				SA_LOG(L"QueryMode: [" << queryMode << L"] not supported yet!", Error, Thread);
				break;
			}
		}
	}

//}

	void ThreadState::SwapBuffers()
	{
		mOutputMutex.lock();

		std::swap(mCurrBuffer, mOutBuffer);

		mOutputMutex.unlock();

		// Notify new output.
		mOnOutput();

		// Reset new current data.
		mResetBuffer(mCurrBuffer);
	}


	bool ThreadState::Submit()
	{
		if (!bIsRunning)
			return false;

		SwapBuffers();

		Yield();

		// Thread still running after yield?
		if (!bIsRunning)
			return false;

		return FetchInput();
	}


	void ThreadState::Update(float _deltaTime)
	{
		mCurrTime = mCurrTime + _deltaTime;
	}


	void ThreadState::Yield()
	{
		// Wait for frequency.
		while (mCurrTime < frequency)
			std::this_thread::yield();

		mCurrTime = std::fmod(mCurrTime, frequency);
	}
}
