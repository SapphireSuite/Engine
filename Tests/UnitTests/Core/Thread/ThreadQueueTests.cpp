// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Collections/Time>

#include <SA/Core/Thread/Queue/ThreadQueue.hpp>
using namespace Sa;

namespace Sa::ThreadQueue_UT
{
	ThreadQueue queue;

	uint32 Count()
	{
		static std::atomic<uint32> count;

		return ++count;
	}



	void Create()
	{
		ThreadQueue::CreateInfos infos;
		infos.threadNum = 4u;

		queue.Create(infos);
	}

	void PushWait1()
	{
		for (uint32 i = 0; i < 10; ++i)
			queue.Push(Time::Sleep, 200_ms);
	}

	void PushWait2()
	{
		for (uint32 i = 0; i < 1000; ++i)
			queue.Push(Time::Sleep, 200_ms);
	}

	void Future()
	{
		for (uint32 i = 0; i < 1000; ++i)
			queue.Push(Count);

		std::future res = queue.Push(Count);
		res.wait();

		SA_UTH_EQ(res.get(), 1001u);
	}

	void Join()
	{
		queue.Join();
	}

	void Destroy()
	{
		queue.Destroy();
	}
}

void ThreadQueueTests()
{
	using namespace ThreadQueue_UT;

	SA_UTH_GP(Create());
	SA_UTH_GP(PushWait1());

	queue.Join();

	SA_UTH_GP(PushWait2());

	queue.Join(ThreadJoinMode::Abandon);

	SA_UTH_GP(Future());

	SA_UTH_GP(PushWait1());

	SA_UTH_GP(Destroy());
}
