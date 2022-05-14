// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_POLYMORPHIC_VECTOR_GUARD
#define SAPPHIRE_ENGINE_POLYMORPHIC_VECTOR_GUARD

#include <vector>
#include <memory>

namespace SA
{
	template <typename T>
	class PolymorphicVector
	{
		std::vector<std::unique_ptr<T>> mVector;

	public:
		class iterator : public std::vector<std::unique_ptr<T>>::iterator
		{
			using std::vector<std::unique_ptr<T>>::iterator::operator->;
			using std::vector<std::unique_ptr<T>>::iterator::operator*;

		public:
			T* operator*()
			{
				auto baseIt = (std::vector<std::unique_ptr<T>>::iterator)(*this);
				return baseIt->get();
			}

			T* operator->()
			{
				auto baseIt = (std::vector<std::unique_ptr<T>>::iterator)(*this);
				return baseIt->get();
			}
		};


		PolymorphicVector() = default;
		PolymorphicVector(PolymorphicVector&&) = default;
		PolymorphicVector(const PolymorphicVector&) = default;

		template <typename DerivT>
		PolymorphicVector(std::vector<DerivT>&& _derivT)
		{
			mVector.reserve(_derivT.size());

			for(auto it = _derivT.begin(); it != _derivT.end(); ++it)
				mVector.emplace_back(new DerivT(std::move(*it)));
		}


		iterator begin()
		{
			return mVector.begin();
		}

		iterator end()
		{
			return mVector.end();
		}


		T* operator[](uint32_t _index)
		{
			return mVector[_index].get();
		}

		const T* operator[](uint32_t _index) const
		{
			return mVector[_index].get();
		}
	};
}

#endif // GUARD
