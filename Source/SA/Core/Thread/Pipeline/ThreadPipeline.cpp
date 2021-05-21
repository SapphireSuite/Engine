// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Thread/Pipeline/ThreadPipeline.hpp>

namespace Sa
{
	ThreadPipeline::ThreadPipeline(const CreateInfos& _infos)
	{
		Create(_infos);
	}

	ThreadAttachment& ThreadPipeline::GetAttachment(unsigned int _index)
	{
		return mThAttachments[_index];
	}

	const ThreadAttachment& ThreadPipeline::GetAttachment(unsigned int _index) const
	{
		return mThAttachments[_index];
	}


	void ThreadPipeline::Create(const CreateInfos& _infos)
	{
		mThAttachments.reserve(_infos.attachInfos.size());

		// Construct.
		for (uint32 i = 0u; i < _infos.attachInfos.size(); ++i)
			mThAttachments.emplace_back(_infos.attachInfos[i], bIsRunning);


		// Init Input attachment.
		for (uint32 i = 0u; i < _infos.attachInfos.size(); ++i)
		{
			unsigned int inAttachIndex = _infos.attachInfos[i].stateInfos.inAttachIndex;

			if(inAttachIndex != static_cast<unsigned int>(-1))
				mThAttachments[i].state.InitInputAttachment(GetAttachment(inAttachIndex).state);
		}


		// Start.
		if (_infos.bStartOnCreate)
			Start();
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
		bIsRunning = true;
	}

	void ThreadPipeline::Update(float _deltaTime)
	{
		for (auto it = mThAttachments.begin(); it != mThAttachments.end(); ++it)
			it->Update(_deltaTime);
	}

	void ThreadPipeline::End()
	{
		bIsRunning = false;

		for (auto it = mThAttachments.begin(); it != mThAttachments.end(); ++it)
			it->Join();
	}
}
