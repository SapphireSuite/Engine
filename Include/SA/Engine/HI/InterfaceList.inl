// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
    template <typename T>
    const typename InterfaceList<T>::DestroyerT InterfaceList<T>::defaultDestroyer = [](T& _in){ _in.Destroy(); };


    template <typename T>
    template <typename... Args>
    T* InterfaceList<T>::Emplace(Args&&... _args)
    {
        return &mObjects.emplace_front(std::forward<Args>(_args)...);
    }

    template <typename T>
    template <typename AT>
    bool InterfaceList<T>::Remove(AT* _object, DestroyerT destroyer)
    {
        static_assert(std::is_base_of<AT, T>::value, "Object to remove must be a base class of T");

        auto prevIt = mObjects.before_begin();

		for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
		{
			if (&*it == _object)
			{
                if(destroyer)
				    destroyer(*it);

				mObjects.erase_after(prevIt);
				
				return true;
			}

            prevIt = it;
		}

        return false;
    }

    template <typename T>
    void InterfaceList<T>::Clear(DestroyerT destroyer)
    {
        if(destroyer)
        {
            for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
                destroyer(*it);
        }

		mObjects.clear();
    }
}
