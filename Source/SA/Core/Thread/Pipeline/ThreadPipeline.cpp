// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Thread/Pipeline/ThreadPipeline.hpp>

namespace Sa
{
	ThreadAttachment& ThreadPipeline::GetAttachment(uint32 _index)
	{
		SA_ASSERT(OutOfRange, Core/Thread, _index, 0u, (uint32)mThAttachments.size());

		return mThAttachments[_index];
	}


	void ThreadPipeline::Create(CreateInfos&& _infos)
	{
		mThAttachments.reserve(_infos.attachInfos.size());

		// Construct.
		for(auto it = _infos.attachInfos.begin(); it != _infos.attachInfos.end(); ++it)
			mThAttachments.emplace_back(std::move(*it), bHasStarted, bIsRunning);


		// Init Input attachment.
		for (uint32 i = 0u; i < (uint32)_infos.attachInfos.size(); ++i)
		{
			const uint32 inAttachIndex = _infos.attachInfos[i].inAttachIndex;

			if (inAttachIndex != uint32(-1))
				mThAttachments[i].state.InitInputAttachment(GetAttachment(inAttachIndex).state);
		}
	}

	void ThreadPipeline::Destroy()
	{
		// Force Join on destroy.
		End();

		// Destroy all.
		mThAttachments.clear();
	}


	void ThreadPipeline::Start()
	{
		bHasStarted = true;
	}

	void ThreadPipeline::Update(float _deltaTime)
	{
		for (auto it = mThAttachments.begin(); it != mThAttachments.end(); ++it)
			it->Update(_deltaTime);
	}

	void ThreadPipeline::End()
	{
		bIsRunning = false;
		bHasStarted = true; // Force start if not.

		for (auto it = mThAttachments.begin(); it != mThAttachments.end(); ++it)
			it->Join();
	}
}
