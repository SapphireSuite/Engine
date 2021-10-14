// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_SPARSE_VECTOR_GUARD
#define SAPPHIRE_SDK_SPARSE_VECTOR_GUARD

#include <vector>
#include <list>

#include <SA/Collections/Debug>

namespace Sa
{
	template <typename T>
	class SparseVector
	{
		std::vector<T> mValues;
		std::list<uint32> mFreeIndices;

	public:
		~SparseVector();

		template <typename... Args>
		T& Emplace(uint32& _id, Args&&... _args);

		void Remove(uint32 _id);

		void Clear();
	};
}

#include <SA/SDK/Misc/SparseVector.inl>

#endif // GUARD
