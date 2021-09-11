// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	namespace Intl
	{
		template <typename T>
		template <typename... Args>
		ResourceHandle<T>::ResourceHandle(Args&&... _args) noexcept :
			handle{ new T{std::forward<Args>(_args)...} }
		{
		}

		template <typename T>
		ResourceHandle<T>::~ResourceHandle()
		{
			delete handle;
		}


		template <typename T>
		void* ResourceHandle<T>::GetHandle() const
		{
			return handle;
		}


		template <typename T, typename DeleterT>
		template <typename... Args>
		ResourceHandleD<T, DeleterT>::ResourceHandleD(DeleterT _deleter, Args&&... _args) noexcept :
			handle{ new T{std::forward<Args>(_args)...} },
			deleter{ _deleter }
		{
		}

		template <typename T, typename DeleterT>
		ResourceHandleD<T, DeleterT>::~ResourceHandleD()
		{
			deleter(*handle);

			delete handle;
		}


		template <typename T, typename DeleterT>
		void* ResourceHandleD<T, DeleterT>::GetHandle() const
		{
			return handle;
		}
	}


	template <typename T, typename... Args>
	T& ResourceHolder::Make(Args&&... _args)
	{
		auto resHandle = new Intl::ResourceHandle<T>(std::forward<Args>(_args)...);

		handles.emplace_back(resHandle);

		return *resHandle->handle;
	}

	template <typename T, typename DeleterT, typename... Args>
	T& ResourceHolder::Make(DeleterT _deleter, Args&&... _args)
	{
		auto resHandle = new Intl::ResourceHandleD<T, DeleterT>(std::move(_deleter), std::forward<Args>(_args)...);

		handles.emplace_back(resHandle);

		return *resHandle->handle;
	}
}
