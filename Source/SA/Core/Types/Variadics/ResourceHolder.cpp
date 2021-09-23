// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Types/Variadics/ResourceHolder.hpp>

namespace Sa
{
	void ResourceHolder::Free(void* _res)
	{
		for (auto it = handles.begin(); it != handles.end(); ++it)
		{
			if ((*it)->GetHandle() == _res)
			{
				delete *it;
				handles.erase(it);
				break;
			}
		}
	}

	void ResourceHolder::FreeAll()
	{
		for (auto it = handles.begin(); it != handles.end(); ++it)
			delete *it;

		handles.clear();
	}
}
