// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <HI/ResourceHolder.hpp>

namespace Sa
{
	ResourceHolder::~ResourceHolder()
	{
		FreeAll();
	}


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
