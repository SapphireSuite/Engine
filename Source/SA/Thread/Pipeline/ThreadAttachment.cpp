// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Thread/Pipeline/ThreadAttachment.hpp>

namespace Sa
{
	ThreadAttachment::ThreadAttachment(CreateInfos&& _infos, std::atomic<float>& _bHasStarted, std::atomic<float>& _bIsRunning) :
		state{ std::move(_infos.stateInfos), _bIsRunning }
	{
		mHandle = std::thread(
			[this, &_bHasStarted](Function<void(ThreadState&)> _main)
			{
				// Wait for start.
				while (!_bHasStarted)
					std::this_thread::yield();

				_main(state);
			},
			
			// Arguments.
			std::move(_infos.main)
		);
	}


	void ThreadAttachment::Update(float _deltaTime)
	{
		state.Update(_deltaTime);
	}

	void ThreadAttachment::Join()
	{
		if (mHandle.joinable())
			mHandle.join();
	}
}
