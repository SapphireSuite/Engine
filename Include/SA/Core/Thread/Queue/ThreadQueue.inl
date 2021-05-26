// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename R, typename... Args>
	std::future<R> ThreadQueue::Push(PackedFunction<R, Args...>&& _func)
	{
		std::promise<R>* hPromise = nullptr;
		ThreadQueueTask task = ThreadQueueTask::Make(hPromise);

		task.handle = std::packaged_task<void()>(
			[hPromise, func{ std::move(_func) }]()
		{
			if constexpr (std::is_same<R, void>::value)
			{
				func();
				hPromise->set_value();
			}
			else
				hPromise->set_value(func());
		}
		);

		AddTask(std::move(task));

		return hPromise->get_future();
	}

	template <typename R, typename... Args>
	std::future<R> ThreadQueue::Push(R(*_func)(Args...), Args... _args)
	{
		return Push(PackedFunction(_func, std::forward<Args>(_args)...));
	}

	template <typename C, typename R, typename... Args>
	std::future<R> ThreadQueue::Push(C* _caller, R(C::* _func)(Args...), Args... _args)
	{
		return Push(PackedFunction(_caller, _func, std::forward<Args>(_args)...));
	}
}
