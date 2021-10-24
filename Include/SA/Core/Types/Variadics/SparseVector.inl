// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
//{ Iterators

	template <typename T>
	SparseVector<T>::Iterator::Iterator(T* _data, const std::list<uint32>& _freeIndices) noexcept :
		mData{ _data },
		mFreeIndices{ _freeIndices }
	{
		mPrevFreeIndexIt = mFreeIndices.crend();
		mNextFreeIndexIt = mFreeIndices.cbegin();

		// mCurrIndex starts at -1.
		IncrementInternal();
	}

	template <typename T>
	void SparseVector<T>::Iterator::IncrementInternal()
	{
		++mCurrIndex;

		while (mNextFreeIndexIt != mFreeIndices.cend() && mCurrIndex == *mNextFreeIndexIt)
		{
			++mCurrIndex;
			--mPrevFreeIndexIt;
			++mNextFreeIndexIt;
		}
	}

	template <typename T>
	void SparseVector<T>::Iterator::DecrementInternal()
	{
		--mCurrIndex;

		while (mPrevFreeIndexIt != mFreeIndices.crend() && mCurrIndex == *mPrevFreeIndexIt)
		{
			--mCurrIndex;
			++mPrevFreeIndexIt;
			--mNextFreeIndexIt;
		}
	}


	template <typename T>
	SparseVector<T>::Iterator SparseVector<T>::Iterator::MakeEnd(T* _data, uint32 _size, const std::list<uint32>& _freeIndices)
	{
		Iterator res(_data, _freeIndices);

		res.mCurrIndex = _size;

		res.mPrevFreeIndexIt = _freeIndices.crbegin();
		res.mNextFreeIndexIt = _freeIndices.cend();

		return res;
	}


	template <typename T>
	SparseVector<T>::Iterator SparseVector<T>::Iterator::operator++(int32 _offset)
	{
		Iterator copy = *this;

		for (uint32 i = 0; i < _offset; ++i)
			IncrementInternal();

		return copy;
	}

	template <typename T>
	SparseVector<T>::Iterator& SparseVector<T>::Iterator::operator++()
	{
		IncrementInternal();

		return *this;
	}


	template <typename T>
	SparseVector<T>::Iterator SparseVector<T>::Iterator::operator--(int32 _offset)
	{
		Iterator copy = *this;

		for (uint32 i = 0; i < _offset; ++i)
			DecrementInternal();

		return copy;
	}

	template <typename T>
	SparseVector<T>::Iterator& SparseVector<T>::Iterator::operator--()
	{
		DecrementInternal();

		return *this;
	}


	template <typename T>
	T& SparseVector<T>::Iterator::operator*() const
	{
		return mData[mCurrIndex];
	}

	template <typename T>
	T* SparseVector<T>::Iterator::operator->() const
	{
		return &mData[mCurrIndex];
	}


	template <typename T>
	bool SparseVector<T>::Iterator::operator==(const Iterator& _rhs) const
	{
		return mData == _rhs.mData && mCurrIndex == _rhs.mCurrIndex;
	}

	template <typename T>
	bool SparseVector<T>::Iterator::operator!=(const Iterator& _rhs) const
	{
		return !(*this == _rhs);
	}



	template <typename T>
	SparseVector<T>::iterator SparseVector<T>::begin()
	{
		return iterator(mData, mFreeIndices);
	}

	template <typename T>
	SparseVector<T>::const_iterator SparseVector<T>::begin() const
	{
		return const_iterator(mData, mFreeIndices);
	}


	template <typename T>
	SparseVector<T>::iterator SparseVector<T>::end()
	{
		return iterator::MakeEnd(mData, mSize, mFreeIndices);
	}

	template <typename T>
	SparseVector<T>::const_iterator SparseVector<T>::end() const
	{
		return const_iterator::MakeEnd(mData, mSize, mFreeIndices);
	}

//}


//{ Constructors

	template <typename T>
	SparseVector<T>::SparseVector(uint32 _capacity)
	{
		Reserve(_capacity);
	}

	template <typename T>
	SparseVector<T>::SparseVector(SparseVector&& _other) noexcept :
		mData{ _other.mData },
		mSize{ _other.mSize},
		mCapacity{ _other.mCapacity },
		mFreeIndices{ std::move(_other.mFreeIndices) }
	{
		_other.mData = nullptr;
		_other.mSize = 0u;
		_other.mCapacity = 0u;
	}

	template <typename T>
	SparseVector<T>::SparseVector(const SparseVector& _other)
	{
	}

	template <typename T>
	SparseVector<T>::~SparseVector()
	{
		Clear();
		::operator delete(mData);
	}

//}


//{ Size/Capacity

	template <typename T>
	bool SparseVector<T>::Empty() const
	{
		return mSize;
	}

	template <typename T>
	uint32 SparseVector<T>::Size() const
	{
		return mSize;
	}

	template <typename T>
	uint32 SparseVector<T>::Capacity() const
	{
		return mCapacity;
	}


	template <typename T>
	void SparseVector<T>::Reserve(uint32 _capacity)
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

	//template <typename T>
	//void SparseVector<T>::Resize(uint32 _size)
	//{
	//}


	template <typename T>
	void SparseVector<T>::Clear()
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

	template <typename T>
	uint32 SparseVector<T>::InsertSpace()
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

	template <typename T>
	template <typename... Args>
	T& SparseVector<T>::ConstructInternal(uint32 _index, Args&&... _args)
	{
		SA_ASSERT(OutOfRange, SA / Core / Containers, _index, 0u, mCapacity);

		new (&mData[_index]) T{ std::forward<Args>(_args)... };

		return mData[_index];
	}


	template <typename T>
	template <typename... Args>
	T& SparseVector<T>::Emplace(Args&&... _args)
	{
		return ConstructInternal(InsertSpace(), std::forward<Args>(_args)...);
	}

	template <typename T>
	template <typename... Args>
	uint32 SparseVector<T>::EmplaceHandle(Args&&... _args)
	{
		const uint32 index = InsertSpace();

		ConstructInternal(index, std::forward<Args>(_args)...);

		return index;
	}


	template <typename T>
	void SparseVector<T>::Remove(T& _object)
	{
		const uint32 index = &_object - mData;

		Remove(index);
	}


	template <typename T>
	void SparseVector<T>::RemoveHandle(uint32 _index)
	{
#if SA_DEBUG

		for (auto index : mFreeIndices)
		{
			if (index == _index)
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

//}
}
