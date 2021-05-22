// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	namespace Intl
	{
		template <typename C, typename R, typename... Args>
		FuncMemberData<C, R, Args...>::FuncMemberData(C* _caller, R(C::* _func)(Args...)) :
			caller{ _caller },
			func{ _func }
		{
			SA_ASSERT(Nullptr, Core/Types, _caller);
			SA_ASSERT(Nullptr, Core/Types, _func);
		}

		template <typename C, typename R, typename... Args>
		R FuncMemberData<C, R, Args...>::InterfaceCall(void* _data, Args... _args)
		{
			FuncMemberData* fData = reinterpret_cast<FuncMemberData*>(_data);

			SA_ASSERT(Nullptr, Core, fData, L"Internal function call: data nullptr!");

			return (fData->caller->*fData->func)(std::forward<Args>(_args)...);
		}
	}

//{ Constructors

	template <typename R, typename... Args>
	Function<R(Args...)>::Function(R(*_func)(Args...)) noexcept :
		mData{ nullptr },
		mSfunc{ _func }
	{
	}

	template <typename R, typename... Args>
	template <typename C>
	Function<R(Args...)>::Function(C* _caller, R(C::* _func)(Args...)) :
		mData{ new Intl::FuncMemberData<C, R, Args...>(_caller, _func) },
		mIntlFunc{ Intl::FuncMemberData<C, R, Args...>::InterfaceCall }
	{
	}

//}

//{ Methods

	template <typename R, typename... Args>
	void Function<R(Args...)>::Set(R(*_func)(Args...))
	{
		if (mData)
		{
			delete mData;
			mData = nullptr;
		}

		mSfunc = _func;
	}

	template <typename R, typename... Args>
	template <typename C>
	void Function<R(Args...)>::Set(C* _caller, R(C::* _func)(Args...))
	{
		if (mData)
		{
			delete mData;
			mData = nullptr;
		}

		mData = new Intl::FuncMemberData<C, R, Args...>(_caller, _func);
		mIntlFunc = Intl::FuncMemberData<C, R, Args...>::InterfaceCall;
	}


	template <typename R, typename... Args>
	void Function<R(Args...)>::Clear()
	{
		if (mData)
		{
			delete mData;
			mData = nullptr;
		}

		mSfunc = nullptr;
	}


	template <typename R, typename... Args>
	bool Function<R(Args...)>::IsEmpty() const noexcept
	{
		return mSfunc == 0;
	}


	template <typename R, typename... Args>
	R Function<R(Args...)>::Execute(Args... _args)
	{
		if (mData)
		{
			SA_ASSERT(Nullptr, Core / Types, mIntlFunc);

			return mIntlFunc(mData, std::forward<Args>(_args)...);
		}
		else
		{
			SA_ASSERT(Nullptr, Core / Types, mSfunc);

			return mSfunc(std::forward<Args>(_args)...);
		}
	}

//}

//{ Operators

	template <typename R, typename... Args>
	Function<R(Args...)>& Function<R(Args...)>::operator=(R(*_func)(Args...)) noexcept
	{
		Set(_func);

		return *this;
	}

	template <typename R, typename... Args>
	R Function<R(Args...)>::operator()(Args... _args)
	{
		return Execute(std::forward<Args>(_args)...);
	}

//}
}
