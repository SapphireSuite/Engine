// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T>
	const T* ThreadState::GetInputBuffer() const
	{
		return static_cast<const T*>(mInBuffer);
	}

	template <typename T>
	T* ThreadState::GetOutputBuffer() const
	{
		return static_cast<T*>(mCurrBuffer);
	}


	template <typename InFuncT, typename OutFuncT>
	void ThreadState::CreateBuffers(const InFuncT& _inBuffFunctor, const OutFuncT& _outBuffFunctor)
	{
		mOutputMutex.lock();

		mInBuffer = _inBuffFunctor();

		mCurrBuffer = _outBuffFunctor();
		mOutBuffer = _outBuffFunctor();

		mOutputMutex.unlock();
	}

	template <typename InFuncT, typename OutFuncT>
	void ThreadState::DestroyBuffers(const InFuncT& _inBuffFunctor, const OutFuncT& _outBuffFunctor)
	{
		mOutputMutex.lock();

		_inBuffFunctor(mInBuffer);

		_outBuffFunctor(mCurrBuffer);
		_outBuffFunctor(mOutBuffer);

		mOutputMutex.unlock();
	}
}
