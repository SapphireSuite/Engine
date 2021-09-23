// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename R, typename... Args>
	Event<R(Args...)>::~Event()
	{
		Clear();
	}


	template <typename R, typename... Args>
	bool Event<R(Args...)>::IsEmpty() const noexcept
	{
		return mFunctions.size() == 0 && mMemberFunctions.size() == 0;
	}

	template <typename R, typename... Args>
	void Event<R(Args...)>::Clear()
	{
		mFunctions.clear();

		for (auto it = mMemberFunctions.begin(); it != mMemberFunctions.end(); ++it)
		{
			SA_ASSERT(Nullptr, Core, it->data, L"Internal function call: data nullptr!");

			delete it->data;
		}

		mMemberFunctions.clear();
	}


	template <typename R, typename... Args>
	void Event<R(Args...)>::Add(R(*_func)(Args...), R* _result)
	{
		SA_ASSERT(Nullptr, Core, _func, L"Add nullptr function!");
		
		(void)_result;

		if constexpr (std::is_same<R, void>::value)
			mFunctions.push_back(FuncHandle{ _func });
		else
			mFunctions.push_back(FuncHandle{ _func, _result });
	}

	template <typename R, typename... Args>
	template <typename C>
	void Event<R(Args...)>::Add(C* _caller, R(C::* _func)(Args...), R* _result)
	{
		SA_ASSERT(Nullptr, Core, _caller, L"Add nullptr caller!");
		SA_ASSERT(Nullptr, Core, _func, L"Add nullptr function!");

		FuncMemberHandle& handle = mMemberFunctions.emplace_back(FuncMemberHandle
		{
			new Intl::FuncMemberData<C, R, Args...>{ _caller, _func },
			Intl::FuncMemberData<C, R, Args...>::InterfaceCall
		});

		(void)handle;
		(void)_result;

		if constexpr (!std::is_same<R, void>::value)
			handle.result = _result;
	}


	template <typename R, typename... Args>
	bool Event<R(Args...)>::Remove(R(*_func)(Args...))
	{
		SA_ASSERT(Nullptr, Core, _func, L"Add nullptr function!");

		for (auto it = mFunctions.begin(); it != mFunctions.end(); ++it)
		{
			if (it->func == _func)
			{
				mFunctions.erase(it);
				return true;
			}
		}

		return false;
	}

	template <typename R, typename... Args>
	template <typename C>
	bool Event<R(Args...)>::Remove(const C* _caller, R(C::* _func)(Args...))
	{
		SA_ASSERT(Nullptr, Core, _caller, L"Add nullptr caller!");
		SA_ASSERT(Nullptr, Core, _func, L"Add nullptr function!");

		for (auto it = mMemberFunctions.begin(); it != mMemberFunctions.end(); ++it)
		{
			Intl::FuncMemberData<C, R, Args...>* data = reinterpret_cast<Intl::FuncMemberData<C, R, Args...>*>(it->data);

			SA_ASSERT(Nullptr, Core, data, L"Internal function call: data nullptr!");
			
			if (data->caller == _caller && data->func == _func)
			{
				delete data;

				mMemberFunctions.erase(it);
				return true;
			}
		}

		return false;
	}


	template <typename R, typename... Args>
	bool Event<R(Args...)>::RRemove(R(*_func)(Args...))
	{
		SA_ASSERT(Nullptr, Core, _func, L"Add nullptr function!");

		for (auto it = mFunctions.rbegin(); it != mFunctions.rend(); ++it)
		{
			if (it->func == _func)
			{
				// Convert rit to it.
				mFunctions.erase((it + 1).base());
				return true;
			}
		}

		return false;
	}

	template <typename R, typename... Args>
	template <typename C>
	bool Event<R(Args...)>::RRemove(const C* _caller, R(C::* _func)(Args...))
	{
		SA_ASSERT(Nullptr, Core, _caller, L"Add nullptr caller!");
		SA_ASSERT(Nullptr, Core, _func, L"Add nullptr function!");

		for (auto it = mMemberFunctions.rbegin(); it != mMemberFunctions.rend(); ++it)
		{
			Intl::FuncMemberData<C, R, Args...>* data = reinterpret_cast<Intl::FuncMemberData<C, R, Args...>*>(it->data);

			SA_ASSERT(Nullptr, Core, data, L"Internal function call: data nullptr!");

			if (data->caller == _caller && data->func == _func)
			{
				delete data;

				// Convert rit to it.
				mMemberFunctions.erase((it + 1).base());
				return true;
			}
		}

		return false;
	}


	template <typename R, typename... Args>
	void Event<R(Args...)>::Execute(const Args&... _args)
	{
		for (auto it = mFunctions.begin(); it != mFunctions.end(); ++it)
		{
			SA_ASSERT(Nullptr, Core, it->func, L"Execute nullptr function!");

			if constexpr (!std::is_same<R, void>::value)
			{
				if (it->result)
				{
					*it->result = it->func(_args...);
					continue;
				}
			}

			it->func(_args...);
		}

		for (auto it = mMemberFunctions.begin(); it != mMemberFunctions.end(); ++it)
		{
			SA_ASSERT(Nullptr, Core, it->func, L"Execute nullptr member function!");

			if constexpr (!std::is_same<R, void>::value)
			{
				if (it->result)
				{
					*it->result = it->func(it->data, _args...);
					continue;
				}

			}

			it->func(it->data, _args...);
		}
	}

	template <typename R, typename... Args>
	void Event<R(Args...)>::Execute(std::vector<R>& _results, const Args&... _args)
	{
		_results.reserve(mFunctions.size() + mMemberFunctions.size());

		for (auto it = mFunctions.begin(); it != mFunctions.end(); ++it)
		{
			SA_ASSERT(Nullptr, Core, it->func, L"Execute nullptr function!");
			
			R& res = _results.emplace_back(it->func(_args...));

			if (it->result)
				*it->result = res;
		}

		for (auto it = mMemberFunctions.begin(); it != mMemberFunctions.end(); ++it)
		{
			SA_ASSERT(Nullptr, Core, it->func, L"Execute nullptr member function!");

			R& res = _results.emplace_back(it->func(it->data, _args...));

			if (it->result)
				*it->result = res;
		}
	}

	template <typename R, typename... Args>
	Event<R(Args...)>& Event<R(Args...)>::operator=(Event&& _other)
	{
		Clear();

		mFunctions = std::move(_other.mFunctions);
		mMemberFunctions = std::move(_other.mMemberFunctions);

		return *this;
	}


	template <typename R, typename... Args>
	Event<R(Args...)>& Event<R(Args...)>::operator+=(R(*_func)(Args...))
	{
		Add(_func);

		return *this;
	}

	template <typename R, typename... Args>
	Event<R(Args...)>& Event<R(Args...)>::operator-=(R(*_func)(Args...))
	{
		Remove(_func);

		return *this;
	}

	template <typename R, typename... Args>
	void Event<R(Args...)>::operator()(const Args&... _args)
	{
		Execute(_args...);
	}

	template <typename R, typename... Args>
	void Event<R(Args...)>::operator()(std::vector<R>& _results, const Args&... _args)
	{
		Execute(_results, _args...);
	}
}
