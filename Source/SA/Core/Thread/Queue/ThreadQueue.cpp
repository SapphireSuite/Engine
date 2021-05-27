// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Thread/Queue/ThreadQueue.hpp>

#include <Collections/Debug>

namespace Sa
{
	void ThreadQueue::Create(const CreateInfos& _infos)
	{
		mWorkers.resize(_infos.threadNum);

		for (auto it = mWorkers.begin(); it != mWorkers.end(); ++it)
			it->Create(*this);
	}

	void ThreadQueue::Destroy()
	{
		Join();

		mIsRunning = false;

		for (auto it = mWorkers.begin(); it != mWorkers.end(); ++it)
			it->Destroy();

		mWorkers.clear();
	}


	bool ThreadQueue::IsRunning() const
	{
		return mIsRunning;
	}

	uint32 ThreadQueue::QueueSize() const
	{
		return mQueueSize;
	}


	void ThreadQueue::OnTaskProcessed(const ThreadQueueTask& _task)
	{
		(void)_task;

		--mProcessingNum;
	}


	void ThreadQueue::AddTask(ThreadQueueTask&& _task)
	{
		std::lock_guard lk(mQueueMutex);

		mTaskQueue.emplace(std::move(_task));

		++mQueueSize;
	}

	bool ThreadQueue::Pop(ThreadQueueTask& _task)
	{
		std::lock_guard lk(mQueueMutex);

		if (mTaskQueue.empty())
			return false;

		_task = std::move(mTaskQueue.front());

		mTaskQueue.pop();

		--mQueueSize;
		++mProcessingNum;

		return true;
	}

	void ThreadQueue::Join(ThreadJoinMode _mode)
	{
		switch (_mode)
		{
			case ThreadJoinMode::Complete:
			{
				// Wait for empty queue and all task processed.
				while (mQueueSize || mProcessingNum)
					std::this_thread::yield();

				break;
			}
			case ThreadJoinMode::Abandon:
			{
				std::lock_guard lk(mQueueMutex);

				mQueueSize = 0;

				while (!mTaskQueue.empty())
					mTaskQueue.pop();

				// Wait for current task processed.
				while (mProcessingNum)
					std::this_thread::yield();

				break;
			}
			default:
			{
				SA_LOG(L"ThreadJoinMode [" << _mode << L"] not supported yet!", Warning, Core);
				break;
			}
		}
	}
}
