// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T>
	SparseVector<T>::~SparseVector()
	{
		Clear();
	}

	template <typename T>
	template <typename... Args>
	T& SparseVector<T>::Emplace(uint32& _id, Args&&... _args)
	{
		if (mFreeIndices.empty())
		{
			_id = (uint32)mValues.size();
			return mValues.emplace_back(std::forward<Args>(_args)...);
		}
		else
		{
			const uint32 index = mFreeIndices.front();
			mFreeIndices.pop_front();

			new (&mValues[index]) T{ std::forward<Args>(_args)... };

			return mValues[index];
		}
	}

	template <typename T>
	void SparseVector<T>::Remove(uint32 _id)
	{
#if SA_DEBUG

		for (auto index : mFreeIndices)
		{
			if (index == _id)
			{
				SA_LOG(L"Index [" << _id << L"] already freed!", Error, SA/SDK);
				return;
			}
		}

		SA_ASSERT(OutOfRange, SA/SDK, _id, 0u, (uint32)mValues.size());

#endif

		mValues[_id].~T();
		mFreeIndices.push_back(_id);
	}

	template <typename T>
	void SparseVector<T>::Clear()
	{
		for (auto index : mFreeIndices)
			new(mValues[index]) T{};

		mValues.clear();
		mFreeIndices.clear();
	}
}
