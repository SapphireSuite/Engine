// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <cmath>

#include <Core/Thread/Pipeline/ThreadState.hpp>
#include <Core/Thread/Pipeline/ThreadPipeline.hpp>

namespace Sa
{
	ThreadState::ThreadState(const CreateInfos& _infos, std::atomic<float>& _bIsRunning) :
		mUserData{ _infos.userData },
		mCopyBuffer{ _infos.copyBuffer },
		mResetBuffer{ _infos.resetBuffer },
		bIsRunning{ _bIsRunning },
		frequency{ _infos.frequency },
		queryMode{ _infos.queryMode },
		inputState{ _infos.inputState }
	{
		if (_infos.inAttachIndex != static_cast<unsigned int>(-1))
		{
			// Added in InitInputAttachment.
			//mInAttach->mOnOutput.Add(this, &ThreadState::SetShouldFetchInAttach);

			mFetchInput = [](void*& _inBuffer, void* _userData)
			{
				// Get this ThreadState.
				return reinterpret_cast<ThreadState*>(_userData)->FetchInAttachment(_inBuffer, _userData);
			};
		}
		else
			mFetchInput = _infos.fetchInput;

		if (_infos.onOutput)
			mOnOutput += _infos.onOutput;
	}

	// Requiered for std::vector compilation but never used.
	ThreadState::ThreadState(ThreadState&& _other) noexcept :
		bIsRunning{ _other.bIsRunning }
	{
	}

	bool ThreadState::IsRunning() const
	{
		return bIsRunning;
	}


	void ThreadState::InitInputAttachment(ThreadState& _inAttach)
	{
		mInAttach = &_inAttach;

		mInAttach->mOnOutput.Add(this, &ThreadState::SetShouldFetchInAttach);
	}

	void ThreadState::CreateBuffers(void* _inBuff, void* _outBuff1, void* _outBuff2)
	{
		mInBuffer = _inBuff;
		mCurrBuffer = _outBuff1;
		mOutBuffer = _outBuff2;
	}

	void ThreadState::DestroyBuffers(void (*_destroyInBuff)(void*), void (*_destroyOutBuff)(void*))
	{
		if (_destroyInBuff)
			_destroyInBuff(mInBuffer);

		if (_destroyOutBuff)
		{
			mOutputMutex.lock();

			_destroyOutBuff(mCurrBuffer);
			_destroyOutBuff(mOutBuffer);

			mOutputMutex.unlock();
		}

		mInBuffer = nullptr;
		mCurrBuffer = nullptr;
		mOutBuffer = nullptr;
	}


	void ThreadState::Update(float _deltaTime)
	{
		mCurrTime = mCurrTime + _deltaTime;
	}

	void ThreadState::Submit()
	{
		// Submit data to output.
		{
			mOutputMutex.lock();

			std::swap(mCurrBuffer, mOutBuffer);

			mOnOutput.Execute(mOutBuffer, mUserData);

			// Handle specific case of move + self submit: copy data before yielding (and any possible move).
			if (queryMode == QueryMode::Move && inputState == InputState::SelfSubmit && !mShouldFetchInAttach)
			{
				// Mutex still locked to prevent from move before copy.

				// Instant use self output as new input.
				QueryOutput(mInBuffer, QueryMode::Copy, false);
			}

			mOutputMutex.unlock();
		}

		// Reset new current data.
		if (mResetBuffer)
			mResetBuffer(mCurrBuffer, mUserData);

		Yield();

		// Thread still running?
		if (bIsRunning)
			FetchInput();
	}


	void ThreadState::Yield()
	{
		// Wait for frequency.
		while (mCurrTime < frequency && bIsRunning)
			std::this_thread::yield();

		mCurrTime = std::fmod(mCurrTime, frequency);
	}

	void ThreadState::FetchInput()
	{
		if (!mFetchInput)
			return;

		// internal use of input attachment?
		void* inUserData = mInAttach ? this : mUserData;

		switch (inputState)
		{
			case InputState::WaitForInSubmit:
			{
				// Wait for query new input success.
				while (bIsRunning && !mFetchInput(mInBuffer, inUserData))
					std::this_thread::yield();

				break;
			}
			case InputState::SelfSubmit:
			{
				// Query new input failed.
				if (!mFetchInput(mInBuffer, inUserData))
				{
					if (queryMode != QueryMode::Move)
					{
						// Use self output as new input.
						QueryOutput(mInBuffer);
					}
				}

				break;
			}
			default:
				break;
		}
	}

	void ThreadState::SetShouldFetchInAttach(void* _outBuff, void* _userData)
	{
		(void)_outBuff;
		(void)_userData;

		mShouldFetchInAttach = true;
	}

	bool ThreadState::FetchInAttachment(void*& _inBuffer, void* _userData)
	{
		(void)_userData;

		if (!mShouldFetchInAttach)
			return false;

		mInAttach->QueryOutput(_inBuffer);

		mShouldFetchInAttach = false;

		return true;
	}

	void ThreadState::QueryOutput(void*& _dst, QueryMode _overrideMode, bool _bLock)
	{
		QueryMode qMode = _overrideMode == QueryMode::None ? queryMode : _overrideMode;

		if(_bLock)
			mOutputMutex.lock_shared(); // Read only

		switch (qMode)
		{
			case QueryMode::Copy:
			{
				if (mCopyBuffer)
					mCopyBuffer(mOutBuffer, _dst);

				break;
			}
			case QueryMode::Move:
			{
				std::swap(mOutBuffer, _dst);
				break;
			}
			default:
				break;
		}

		if (_bLock)
			mOutputMutex.unlock_shared(); // Read only
	}
}
