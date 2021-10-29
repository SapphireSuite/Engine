// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_SPARSE_VECTOR_GUARD
#define SAPPHIRE_SDK_SPARSE_VECTOR_GUARD

#include <list>

#include <SA/Core/Types/Handle.hpp>
#include <SA/Core/Algorithms/MemMove.hpp>

#include <SA/Collections/Debug>

namespace Sa
{
	template <typename T>
	class SparseVectorHandle;


//{ Vector

	namespace Intl
	{
		template <typename HandleT>
		class SparseVectorBase
		{
		public:
			virtual HandleT* At(uint32 _index) = 0;
			virtual const HandleT* At(uint32 _index) const = 0;
		};
	}

	template <typename T, typename HandleT = T>
	class SparseVector : public Intl::SparseVectorBase<HandleT>
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
		*	Erase object at index.
		* 
		*	\param[in] _index	index to erase at.
		*/
		void EraseAtIndex(uint32 _index);

		/**
		*	Construct new object in-place at index with args.
		* 
		*	\param[in] _index	index to construct at.
		*	\param[in] _args	arguments to construct new object with.
		*/
		template <typename... Args>
		T& ConstructInternal(uint32 _index, Args&&... _args);

	public:
		using SparseHandleT = typename SparseVectorHandle<HandleT>;

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
		SparseHandleT EmplaceHandle(Args&&... _args);

		void Erase(T& _object);
		void EraseHandle(const SparseHandleT& _handle);

//}


//{ Accessors
		
		HandleT* At(uint32 _index) override final;
		const HandleT* At(uint32 _index) const override final;

		T& operator[](uint64 _index);
		const T& operator[](uint64 _index) const;

//}
	};

//}


//{ Handle

	template <typename HandleT>
	class SparseVectorHandle : public Handle
	{
		Intl::SparseVectorBase<HandleT>* mVector = nullptr;

		using Handle::Handle;

	public:
		SparseVectorHandle() = default;
		SparseVectorHandle(uint64 _id, Intl::SparseVectorBase<HandleT>& _vec);

		/**
		*	\brief Get Handled object.
		* 
		*	\return Handled object if valid, otherwise nullptr.
		*/
		HandleT* Get();

		/**
		*	\brief Get \b const Handled object.
		* 
		*	\return \b const Handled object if valid, otherwise nullptr.
		*/
		const HandleT* Get() const;


		bool IsValid() const noexcept override;

		void Reset() noexcept override;
	};

//}
}

#include <SA/Core/Types/Variadics/SparseVector.inl>

#endif // GUARD
