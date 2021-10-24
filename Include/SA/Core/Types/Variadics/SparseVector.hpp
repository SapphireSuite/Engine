// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_SPARSE_VECTOR_GUARD
#define SAPPHIRE_SDK_SPARSE_VECTOR_GUARD

#include <list>

#include <SA/Core/Algorithms/MemMove.hpp>

#include <SA/Collections/Debug>

namespace Sa
{
	template <typename T>
	class SparseVector
	{
		T* mData = nullptr;

		/// Maximum size.
		uint32 mSize = 0u;
		uint32 mCapacity = 0u;

		std::list<uint32> mFreeIndices;

		/**
		*	Insert space for new object.
		* 
		*	\return index to insert new object in.
		*/
		uint32 InsertSpace();

		/**
		*	Construct new object in-place at index with args.
		* 
		*	\param[in] _index	index to construct at.
		*	\param[in] _args	arguments to construct new object with.
		*/
		template <typename... Args>
		T& ConstructInternal(uint32 _index, Args&&... _args);

	public:
		SparseVector(uint32 _capacity = 5u);
		SparseVector(SparseVector&& _other) noexcept;
		SparseVector(const SparseVector& _other);
		~SparseVector();

		bool Empty() const;
		uint32 Size() const;
		uint32 Capacity() const;

		void Reserve(uint32 _capacity);
		//void Resize(uint32 _size);

		/**
		*	Emplace new element in-place with args.
		* 
		*	\param[in] _args	arguments to construct new object from.
		*/
		template <typename... Args>
		T& Emplace(Args&&... _args);

		/**
		*	Emplace new element in-place with args.
		*	Return index for handle.
		*
		*	\param[in] _args	arguments to construct new object from.
		* 
		*	\return index of emplaced object.
		*/
		template <typename... Args>
		uint32 EmplaceHandle(Args&&... _args);

		void Remove(uint32 _index);
		void Remove(T& _object);

		void Clear();
	};
}

#include <SA/Core/Types/Variadics/SparseVector.inl>

#endif // GUARD
