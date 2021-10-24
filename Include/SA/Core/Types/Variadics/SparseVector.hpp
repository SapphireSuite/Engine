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
//{ Iterators

		class Iterator
		{
		public:
			Iterator(T* _data, const std::list<uint32>& _freeIndices) noexcept;

			static Iterator MakeEnd(T* _data, uint32 _size, const std::list<uint32>& _freeIndices);


			Iterator  operator++(int32 _offset);
			Iterator& operator++();

			Iterator  operator--(int32 _offset);
			Iterator& operator--();

			T& operator* () const;
			T* operator->() const;

			bool operator==(const Iterator& _rhs) const;
			bool operator!=(const Iterator& _rhs) const;

		private:
			T* mData;
			uint32 mCurrIndex = uint32(-1);
			const std::list<uint32>& mFreeIndices;
			std::list<uint32>::const_reverse_iterator mPrevFreeIndexIt;
			std::list<uint32>::const_iterator mNextFreeIndexIt;

			void IncrementInternal();
			void DecrementInternal();
		};

		using iterator = Iterator;
		using const_iterator = SparseVector<const T>::Iterator;

		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;

//}


//{ Constructors

		SparseVector(uint32 _capacity = 5u);
		SparseVector(SparseVector&& _other) noexcept;
		SparseVector(const SparseVector& _other);
		~SparseVector();

//}


//{ Size/Capacity

		bool Empty() const;
		uint32 Size() const;
		uint32 Capacity() const;

		void Reserve(uint32 _capacity);
		//void Resize(uint32 _size);

		void Clear();
//}


//{ Add/Remove

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

		void Remove(T& _object);
		void RemoveHandle(uint32 _index);

//}
	};
}

#include <SA/Core/Types/Variadics/SparseVector.inl>

#endif // GUARD
