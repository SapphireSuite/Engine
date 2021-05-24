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
		FuncMemberDataBase* FuncMemberData<C, R, Args...>::Duplicate() const
		{
			return new FuncMemberData(caller, func);
		}

		template <typename C, typename R, typename... Args>
		bool FuncMemberData<C, R, Args...>::Compare(const FuncMemberDataBase* _other) const
		{
			SA_ASSERT(Nullptr, Core/Types, _other);
			const FuncMemberData* memData = reinterpret_cast<const FuncMemberData*>(_other);

			return reinterpret_cast<uint64>(caller) && reinterpret_cast<uint64>(memData->caller) && func == memData->func;
		}


		template <typename C, typename R, typename... Args>
		R FuncMemberData<C, R, Args...>::InterfaceCall(void* _data, Args... _args)
		{
			FuncMemberData* fData = reinterpret_cast<FuncMemberData*>(_data);

			SA_ASSERT(Nullptr, Core, fData, L"Internal function call: data nullptr!");

			return (fData->caller->*fData->func)(std::forward<Args>(_args)...);
		}
	}

//{ Function

//{ Constructors

	template <typename R, typename... Args>
	Function<R(Args...)>::Function(R(*_func)(Args...)) noexcept :
		mData{ nullptr },
		mSFunc{ _func }
	{
	}

	template <typename R, typename... Args>
	template <typename C>
	Function<R(Args...)>::Function(C* _caller, R(C::* _func)(Args...)) :
		mData{ new Intl::FuncMemberData<C, R, Args...>(_caller, _func) },
		mIntlFunc{ Intl::FuncMemberData<C, R, Args...>::InterfaceCall }
	{
	}


	template <typename R, typename... Args>
	Function<R(Args...)>::Function(Function&& _other) noexcept
	{
		if (_other.mData)
		{
			mData = _other.mData;
			_other.mData = nullptr;

			mIntlFunc = _other.mIntlFunc;
			_other.mIntlFunc = nullptr;
		}
		else
		{
			mSFunc = _other.mSFunc;
			_other.mSFunc = nullptr;
		}
	}

	template <typename R, typename... Args>
	Function<R(Args...)>::Function(const Function& _other) noexcept
	{
		if (_other.mData)
		{
			mData = _other.mData->Duplicate();
			mIntlFunc = _other.mIntlFunc;
		}
		else
			mSFunc = _other.mSFunc;
	}

	template <typename R, typename... Args>
	Function<R(Args...)>::~Function()
	{
		Clear();
	}

//}

//{ Equals

	template <typename R, typename... Args>
	bool Function<R(Args...)>::IsEmpty() const noexcept
	{
		return !mSFunc;
	}

	template <typename R, typename... Args>
	Function<R(Args...)>::operator bool() const
	{
		return mSFunc;
	}


	template <typename R, typename... Args>
	bool Function<R(Args...)>::Equals(const Function& _other) const
	{
		if (mData)
		{
			if (_other.mData)
				return mData->Compare(_other.mData);
		}
		else if (mSFunc)
			return mSFunc == _other.mSFunc;

		return false;
	}

	template <typename R, typename... Args>
	bool Function<R(Args...)>::operator==(const Function& _rhs) const
	{
		return Equals(_rhs);
	}

	template <typename R, typename... Args>
	bool Function<R(Args...)>::operator!=(const Function& _rhs) const
	{
		return !Equals(_rhs);
	}

//}

//{ Set

	template <typename R, typename... Args>
	void Function<R(Args...)>::Clear()
	{
		if (mData)
		{
			delete mData;
			mData = nullptr;
		}

		mSFunc = nullptr;
	}


	template <typename R, typename... Args>
	void Function<R(Args...)>::Set(R(*_func)(Args...))
	{
		Clear();

		mSFunc = _func;
	}

	template <typename R, typename... Args>
	template <typename C>
	void Function<R(Args...)>::Set(C* _caller, R(C::* _func)(Args...))
	{
		Clear();

		mData = new Intl::FuncMemberData<C, R, Args...>(_caller, _func);
		mIntlFunc = Intl::FuncMemberData<C, R, Args...>::InterfaceCall;
	}


	template <typename R, typename... Args>
	Function<R(Args...)>& Function<R(Args...)>::operator=(Function&& _rhs) noexcept
	{
		Clear();

		if (_rhs.mData)
		{
			mData = _rhs.mData;
			_rhs.mData = nullptr;

			mIntlFunc = _rhs.mIntlFunc;
			_rhs.mIntlFunc = nullptr;
		}
		else
		{
			mSFunc = _rhs.mSFunc;
			_rhs.mSFunc = nullptr;
		}

		return *this;
	}


	template <typename R, typename... Args>
	Function<R(Args...)>& Function<R(Args...)>::operator=(const Function& _rhs) noexcept
	{
		Clear();

		if (_rhs.mData)
		{
			mData = _rhs.mData->Duplicate();
			mIntlFunc = _rhs.mIntlFunc;
		}
		else
			mSFunc = _rhs.mSFunc;

		return *this;
	}


	template <typename R, typename... Args>
	Function<R(Args...)>& Function<R(Args...)>::operator=(R(*_func)(Args...)) noexcept
	{
		Set(_func);

		return *this;
	}
//}

//{ Execute

	template <typename R, typename... Args>
	R Function<R(Args...)>::Execute(Args... _args) const
	{
		if (mData)
			return mIntlFunc(mData, std::forward<Args>(_args)...);
		else if(mSFunc)
			return mSFunc(std::forward<Args>(_args)...);

		return R();
	}

	template <typename R, typename... Args>
	R Function<R(Args...)>::operator()(Args... _args) const
	{
		return Execute(std::forward<Args>(_args)...);
	}

//}

//}

//{ PackedFunction

//{ Constructors

	template <typename R, typename... Args>
	PackedFunction<R(Args...)>::PackedFunction(R(*_func)(Args...), Args... _args) noexcept :
		Function<R(Args...)>(_func),
		mArgs{ std::forward<Args>(_args)... }
	{
	}

	template <typename R, typename... Args>
	template <typename C>
	PackedFunction<R(Args...)>::PackedFunction(C* _caller, R(C::* _func)(Args...), Args... _args) :
		Function<R(Args...)>(_caller, _func),
		mArgs{ std::forward<Args>(_args)... }
	{
	}


	template <typename R, typename... Args>
	PackedFunction<R(Args...)>::PackedFunction(PackedFunction&& _other) noexcept :
		Function<R(Args...)>(std::move(_other)),
		mArgs{ std::move(_other.mArgs) }
	{
	}

	template <typename R, typename... Args>
	PackedFunction<R(Args...)>::PackedFunction(const PackedFunction& _other) noexcept :
		Function<R(Args...)>(_other),
		mArgs{ _other.mArgs }
	{
	}
//}

//{ Equals

	template <typename R, typename... Args>
	bool PackedFunction<R(Args...)>::Equals(const PackedFunction& _other) const
	{
		return Function<R(Args...)>::Equals(_other) && mArgs == _other.mArgs;
	}

	template <typename R, typename... Args>
	bool PackedFunction<R(Args...)>::operator==(const PackedFunction& _rhs) const
	{
		return Equals(_rhs);
	}

	template <typename R, typename... Args>
	bool PackedFunction<R(Args...)>::operator!=(const PackedFunction& _rhs) const
	{
		return !Equals(_rhs);
	}

//}

//{ Set

	template <typename R, typename... Args>
	void PackedFunction<R(Args...)>::Set(R(*_func)(Args...), Args... _args)
	{
		Function<R(Args...)>::Set(_func);
		mArgs = std::tuple<Args...>{ std::forward<Args>(_args)... };
	}

	template <typename R, typename... Args>
	template <typename C>
	void PackedFunction<R(Args...)>::Set(C* _caller, R(C::* _func)(Args...), Args... _args)
	{
		Function<R(Args...)>::Set(_caller, _func);
		mArgs = std::tuple<Args...>{ std::forward<Args>(_args)... };
	}


	template <typename R, typename... Args>
	PackedFunction<R(Args...)>& PackedFunction<R(Args...)>::operator=(PackedFunction&& _rhs) noexcept
	{
		Function<R(Args...)>::operator=(std::move(_rhs));
		mArgs = std::move(_rhs.mArgs);

		return *this;
	}

	template <typename R, typename... Args>
	PackedFunction<R(Args...)>& PackedFunction<R(Args...)>::operator=(const PackedFunction& _rhs) noexcept
	{
		Function<R(Args...)>::operator=(_rhs);
		mArgs = _rhs.mArgs;

		return *this;
	}

	//}

	//{ Execute

	template <typename R, typename... Args>
	R PackedFunction<R(Args...)>::Execute() const
	{
		const Function<R(Args...)>& fThis = *this;

		return std::apply(fThis, mArgs);
	}


	template <typename R, typename... Args>
	R PackedFunction<R(Args...)>::operator()() const
	{
		return Execute();
	}

//}

//}
}
