// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Collections/Time>

#include <SA/Core/Thread/Queue/ThreadQueue.hpp>
using namespace Sa;

namespace Sa::ThreadQueue_UT
{
	ThreadQueue queue;

	class A
	{
	public:
		void Foo()
		{
			SA_LOG("A::Foo()");
		}
	};

	std::atomic<uint32> count;
	uint32 Count()
	{
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

		queue.Join();

		std::future res = queue.Push(Count);
		res.wait();

		SA_UTH_EQ(res.get(), 1001u);

		A a;
		queue.Push(&a, &A::Foo);
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

	SA_UTH_GP(queue.Join());

	SA_UTH_GP(PushWait2());

	SA_UTH_GP(queue.Join(ThreadJoinMode::Abandon));

	SA_UTH_GP(Future());

	SA_UTH_GP(PushWait1());

	SA_UTH_GP(Destroy());
}
