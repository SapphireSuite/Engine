// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RESOURCE_HOLDER_GUARD
#define SAPPHIRE_ENGINE_RESOURCE_HOLDER_GUARD

#include <vector>

namespace Sa
{
	namespace Intl
	{
		class ResourceHandleBase
		{
		public:
			virtual ~ResourceHandleBase() = default;

			virtual void* GetHandle() const = 0;
		};


		template <typename T>
		class ResourceHandle : public ResourceHandleBase
		{
		public:
			T* handle = nullptr;

			template <typename... Args>
			ResourceHandle(Args&&... _args) noexcept;
			~ResourceHandle();

			void* GetHandle() const override final;
		};


		template <typename T, typename DeleterT>
		class ResourceHandleD : public ResourceHandleBase
		{
		public:
			T* handle = nullptr;
			DeleterT deleter;

			template <typename... Args>
			ResourceHandleD(DeleterT _deleter, Args&&... _args) noexcept;
			~ResourceHandleD();

			void* GetHandle() const override final;
		};
	}

	class ResourceHolder
	{
		std::vector<Intl::ResourceHandleBase*> handles;

	public:
		~ResourceHolder();

		template <typename T, typename... Args>
		T& Make(Args&&... _args);

		template <typename T, typename DeleterT, typename... Args>
		T& Make(DeleterT _deleter, Args&&... _args);

		void Free(void* _res);
		void FreeAll();
	};
}

#include <SA/Engine/HI/ResourceHolder.inl>

#endif // GUARD
