// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
//{ Iterators

	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::Iterator::Iterator(T* _data, const std::list<uint32>& _freeIndices) noexcept :
		mData{ _data },
		mFreeIndices{ _freeIndices }
	{
		mPrevFreeIndexIt = mFreeIndices.crend();
		mNextFreeIndexIt = mFreeIndices.cbegin();

		// mCurrIndex starts at -1.
		IncrementInternal();
	}

	template <typename T, typename HandleT>
	void SparseVector<T, HandleT>::Iterator::IncrementInternal()
	{
		++mCurrIndex;

		while (mNextFreeIndexIt != mFreeIndices.cend() && mCurrIndex == *mNextFreeIndexIt)
		{
			++mCurrIndex;
			--mPrevFreeIndexIt;
			++mNextFreeIndexIt;
		}
	}

	template <typename T, typename HandleT>
	void SparseVector<T, HandleT>::Iterator::DecrementInternal()
	{
		--mCurrIndex;

		while (mPrevFreeIndexIt != mFreeIndices.crend() && mCurrIndex == *mPrevFreeIndexIt)
		{
			--mCurrIndex;
			++mPrevFreeIndexIt;
			--mNextFreeIndexIt;
		}
	}


	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::Iterator SparseVector<T, HandleT>::Iterator::MakeEnd(T* _data, uint32 _size, const std::list<uint32>& _freeIndices)
	{
		Iterator res(_data, _freeIndices);

		res.mCurrIndex = _size;

		res.mPrevFreeIndexIt = _freeIndices.crbegin();
		res.mNextFreeIndexIt = _freeIndices.cend();

		return res;
	}


	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::Iterator SparseVector<T, HandleT>::Iterator::operator++(int32 _offset)
	{
		Iterator copy = *this;

		for (uint32 i = 0; i < _offset; ++i)
			IncrementInternal();

		return copy;
	}

	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::Iterator& SparseVector<T, HandleT>::Iterator::operator++()
	{
		IncrementInternal();

		return *this;
	}


	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::Iterator SparseVector<T, HandleT>::Iterator::operator--(int32 _offset)
	{
		Iterator copy = *this;

		for (uint32 i = 0; i < _offset; ++i)
			DecrementInternal();

		return copy;
	}

	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::Iterator& SparseVector<T, HandleT>::Iterator::operator--()
	{
		DecrementInternal();

		return *this;
	}


	template <typename T, typename HandleT>
	T& SparseVector<T, HandleT>::Iterator::operator*() const
	{
		return mData[mCurrIndex];
	}

	template <typename T, typename HandleT>
	T* SparseVector<T, HandleT>::Iterator::operator->() const
	{
		return &mData[mCurrIndex];
	}


	template <typename T, typename HandleT>
	bool SparseVector<T, HandleT>::Iterator::operator==(const Iterator& _rhs) const
	{
		return mData == _rhs.mData && mCurrIndex == _rhs.mCurrIndex;
	}

	template <typename T, typename HandleT>
	bool SparseVector<T, HandleT>::Iterator::operator!=(const Iterator& _rhs) const
	{
		return !(*this == _rhs);
	}



	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::iterator SparseVector<T, HandleT>::begin()
	{
		return iterator(mData, mFreeIndices);
	}

	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::const_iterator SparseVector<T, HandleT>::begin() const
	{
		return const_iterator(mData, mFreeIndices);
	}


	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::iterator SparseVector<T, HandleT>::end()
	{
		return iterator::MakeEnd(mData, mSize, mFreeIndices);
	}

	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::const_iterator SparseVector<T, HandleT>::end() const
	{
		return const_iterator::MakeEnd(mData, mSize, mFreeIndices);
	}

//}


//{ Constructors

	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::SparseVector(uint32 _capacity)
	{
		Reserve(_capacity);
	}

	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::SparseVector(SparseVector&& _other) noexcept :
		mData{ _other.mData },
		mSize{ _other.mSize},
		mCapacity{ _other.mCapacity },
		mFreeIndices{ std::move(_other.mFreeIndices) }
	{
		_other.mData = nullptr;
		_other.mSize = 0u;
		_other.mCapacity = 0u;
	}

	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::SparseVector(const SparseVector& _other)
	{
	}

	template <typename T, typename HandleT>
	SparseVector<T, HandleT>::~SparseVector()
	{
		Clear();
		::operator delete(mData);
	}

//}


//{ Size/Capacity

	template <typename T, typename HandleT>
	bool SparseVector<T, HandleT>::Empty() const
	{
		return mSize;
	}

	template <typename T, typename HandleT>
	uint32 SparseVector<T, HandleT>::Size() const
	{
		return mSize;
	}

	template <typename T, typename HandleT>
	uint32 SparseVector<T, HandleT>::Capacity() const
	{
		return mCapacity;
	}


	template <typename T, typename HandleT>
	void SparseVector<T, HandleT>::Reserve(uint32 _capacity)
	{
		if (mCapacity > _capacity)
			return;

		T* const newData = static_cast<T*>(::operator new(_capacity * sizeof(T)));

		if (mSize)
			MemMove(mData, newData, mSize);

		// Can have data with no size.
		if (mData)
			::operator delete(mData);

		mData = newData;

		mCapacity = _capacity;
	}

	//template <typename T, typename HandleT>
	//void SparseVector<T, HandleT>::Resize(uint32 _size)
	//{
	//}


	template <typename T, typename HandleT>
	void SparseVector<T, HandleT>::Clear()
	{
		uint32 index = uint32(-1);
		uint32 currFreeIndex = uint32(-1);

		do
		{
			if (index == currFreeIndex)
			{
				if (!mFreeIndices.empty())
				{
					currFreeIndex = mFreeIndices.front();
					mFreeIndices.pop_front();
				}
			}
			else
			{
				mData[index].~T();
			}

			++index;
		} while (index < mSize);

		mSize = 0u;
	}

//}


//{ Add/Remove

	template <typename T, typename HandleT>
	uint32 SparseVector<T, HandleT>::InsertSpace()
	{
		uint32 index = uint32(-1);

		// Emplace in empty space.
		if (!mFreeIndices.empty())
		{
			index = mFreeIndices.front();
			mFreeIndices.pop_front();
		}
		else
		{
			// No empty space: increase size.

			// Should re-allocate?
			if (mSize + 1 > mCapacity)
				Reserve(mCapacity * 2u);

			index = mSize++;
		}

		return index;
	}

	template <typename T, typename HandleT>
	void SparseVector<T, HandleT>::EraseAtIndex(uint32 _index)
	{
		SA_ASSERT(OutOfRange, SA/Core/Containers, _index, 0u, mSize, L"Erase index is out of range!");

#if SA_DEBUG

		for (auto freeIndex : mFreeIndices)
		{
			if (freeIndex == _index)
			{
				SA_LOG(L"Index [" << _index << L"] already freed!", Error, SA/Core/Containers);
				return;
			}
		}

		SA_ASSERT(OutOfRange, SA/Core/Containers, _index, 0u, mSize);

#endif

		// Desctruct object.
		mData[_index].~T();
		mFreeIndices.push_back(_index);
	}

	template <typename T, typename HandleT>
	template <typename... Args>
	T& SparseVector<T, HandleT>::ConstructInternal(uint32 _index, Args&&... _args)
	{
		SA_ASSERT(OutOfRange, SA / Core / Containers, _index, 0u, mCapacity);

		new (&mData[_index]) T{ std::forward<Args>(_args)... };

		return mData[_index];
	}


	template <typename T, typename HandleT>
	template <typename... Args>
	T& SparseVector<T, HandleT>::Emplace(Args&&... _args)
	{
		return ConstructInternal(InsertSpace(), std::forward<Args>(_args)...);
	}

	template <typename T, typename HandleT>
	template <typename... Args>
	SparseVector<T, HandleT>::SparseHandleT SparseVector<T, HandleT>::EmplaceHandle(Args&&... _args)
	{
		const uint32 index = InsertSpace();

		ConstructInternal(index, std::forward<Args>(_args)...);

		return SparseHandleT(index, *this);
	}


	template <typename T, typename HandleT>
	void SparseVector<T, HandleT>::Erase(T& _object)
	{
		const uint32 index = &_object - mData;

		EraseAtIndex(index);
	}

	template <typename T, typename HandleT>
	void SparseVector<T, HandleT>::EraseHandle(const SparseHandleT& _handle)
	{
		const uint32 index = static_cast<uint32>(_handle.ID);
		
		EraseAtIndex(index);
	}

//}


//{ Accessors
		
	template <typename T, typename HandleT>
	HandleT* SparseVector<T, HandleT>::At(uint32 _index)
	{
		SA_ASSERT(OutOfRange, SA/Core/Containers, _index, 0u, mSize);

		return &mData[_index];
	}

	template <typename T, typename HandleT>
	const HandleT* SparseVector<T, HandleT>::At(uint32 _index) const
	{
		SA_ASSERT(OutOfRange, SA/Core/Containers, _index, 0u, mSize);

		return &mData[_index];
	}


	template <typename T, typename HandleT>
	T& SparseVector<T, HandleT>::operator[](uint64 _index)
	{
		SA_ASSERT(OutOfRange, SA/Core/Containers, (uint32)_index, 0u, mSize);

		return mData[_index];
	}

	template <typename T, typename HandleT>
	const T& SparseVector<T, HandleT>::operator[](uint64 _index) const
	{
		SA_ASSERT(OutOfRange, SA/Core/Containers, (uint32)_index, 0u, mSize);

		return mData[_index];
	}

//}


//{ Handle

	template <typename HandleT>
	SparseVectorHandle<HandleT>::SparseVectorHandle(uint64 _id, Intl::SparseVectorBase<HandleT>& _vec) :
		Handle(_id),
		mVector{ &_vec }
	{
	}


	template <typename HandleT>
	HandleT* SparseVectorHandle<HandleT>::Get()
	{
		if (!IsValid())
			return nullptr;

		return mVector->At(static_cast<uint32>(ID));
	}

	template <typename HandleT>
	const HandleT* SparseVectorHandle<HandleT>::Get() const
	{
		if (!IsValid())
			return nullptr;

		return mVector->At(static_cast<uint32>(ID));
	}


	template <typename HandleT>
	bool SparseVectorHandle<HandleT>::IsValid() const noexcept
	{
		return Handle::IsValid() && mVector;
	}

	template <typename HandleT>
	void SparseVectorHandle<HandleT>::Reset() noexcept
	{
		Handle::Reset();
		mVector = nullptr;
	}

//}
}
