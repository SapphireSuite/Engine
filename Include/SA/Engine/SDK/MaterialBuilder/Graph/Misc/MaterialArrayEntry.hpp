// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_ARRAY_ENTRY_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_ARRAY_ENTRY_GUARD

#include <vector>

#include <SA/Collections/Debug>

namespace SA::SDK
{
	template <typename T>
	class MaterialArrayEntry
	{
		std::vector<T> mEntries;

	public:
		void AddEntry(T _input, uint32_t _pos = ~uint32_t())
		{
			auto it = mEntries.end();

			if(_pos != ~uint32_t())
			{
				SA_ASSERT(OutOfArrayRange, SA/Engine/SDK/MaterialBuilder, _pos, mEntries);

				it = mEntries.begin() + _pos;
			}

			mEntries.insert(it, _input);
		}


		void RemoveEntry(T _input, bool bRemoveAllInstance = false)
		{
			for(auto it = mEntries.begin(); it != mEntries.end();)
			{
				if (*it == _input)
				{
					it = mEntries.erase(it);

					if(!bRemoveAllInstance)
						return;
				}
				else
					it++;
			}
		}

		void RemoveEntry(uint32_t _pos)
		{
			SA_ASSERT(OutOfArrayRange, SA/Engine/SDK/MaterialBuilder, _pos, mEntries);

			mEntries.erase(mEntries.begin() + _pos);
		}

		// InputIterator begin();
		// InputIterator end();
	};
}

#endif // GUARD
