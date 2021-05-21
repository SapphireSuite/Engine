// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <thread>

#include <Core/Thread/Pipeline/ThreadAttachment.hpp>

namespace Sa
{
	ThreadAttachment::ThreadAttachment(const CreateInfos& _infos, std::atomic<float>& _bIsRunning) :
		state{ _infos.stateInfos, _bIsRunning }
	{
		auto thMethod = _infos.method;

		mHandle = std::thread([this, thMethod]()
		{
			// Wait for start.
			while(!state.IsRunning())
				std::this_thread::yield();

			thMethod(state);
		});
	}


	void ThreadAttachment::Update(float _deltaTime)
	{
		state.Update(_deltaTime);
	}

	void ThreadAttachment::Join()
	{
		if(mHandle.joinable())
			mHandle.join();
	}
}
