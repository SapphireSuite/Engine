// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
    template <typename T>
    InterfaceList<T>::InterfaceList() noexcept
    {
        static_assert(std::is_base_of<HardwareInterface, T>::value, L"Handled interface type should inherit from HardwareInterface");
    }


    template <typename T>
    template <typename... Args>
    T* InterfaceList<T>::Emplace(Args&&... _args)
    {
        return &mObjects.emplace_front(std::forward<Args>(_args)...);
    }

    template <typename T>
    template <typename AT, typename DestroyFunctor>
    bool InterfaceList<T>::Erase(AT* _object, DestroyFunctor _destroyer)
    {
        static_assert(std::is_base_of<AT, T>::value, "Object to remove must be a base class of T");

        auto prevIt = mObjects.before_begin();

		for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
		{
			if (&*it == _object)
			{
				_destroyer(*it);
				mObjects.erase_after(prevIt);
				
				return true;
			}

            prevIt = it;
		}

        SA_LOG(L"Object [" << _object << L"] not found in list", Error, SA/Engine/HI);

        return false;
    }



    template <typename T>
    template <typename DestroyFunctor>
    void InterfaceList<T>::Clear(DestroyFunctor _destroyer)
    {
        for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
            _destroyer(*it);

		mObjects.clear();
    }
}
