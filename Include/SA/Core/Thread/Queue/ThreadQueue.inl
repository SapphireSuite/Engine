// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename R, typename... Args>
	std::future<R> ThreadQueue::Push(R(*_func)(Args...), Args&&... _args)
	{
		ThreadQueueTask task;
		task.promise = std::make_unique<Intl::ThreadPromise<R>>();
		std::promise<R>* hPromise = &reinterpret_cast<Intl::ThreadPromise<R>*>(task.promise.get())->handle;

		task.handle = std::packaged_task<void()>(
			[hPromise, _func, &_args...]()
			{
				if constexpr (std::is_same<R, void>::value)
				{
					_func(_args...);
					//_func(std::forward<Args>(_args)...);
					hPromise->set_value();
				}
				else
					hPromise->set_value(_func(_args...));
				//hPromise->set_value(_func(std::forward<Args>(_args)...));
			}
		);

		AddTask(std::move(task));

		return hPromise->get_future();
	}
}
