// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename R>
	ThreadQueueTask ThreadQueueTask::Make(std::promise<R>*& _hPromise)
	{
		ThreadQueueTask res;

		auto promise = std::make_unique<Intl::ThreadPromise<R>>();

		_hPromise = &promise->handle;

		res.promise = std::move(promise);

		return res;
	}
}
