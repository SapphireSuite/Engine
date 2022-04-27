// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_INTERFACE_LIST_GUARD
#define SAPPHIRE_ENGINE_INTERFACE_LIST_GUARD

#include <forward_list>

namespace Sa
{
// { Functor

    template <typename T>
    struct NoneFunctor
    {
        void operator()(T& _in) { (void)_in; };
    };

//}


    template <typename T>
    class InterfaceList
    {
        std::forward_list<T> mObjects;

    public:
        InterfaceList() noexcept;

        template <typename... Args>
        T* Emplace(Args&&... _args);

        /**
         * @brief 
         * 
         * @tparam AT       Abstract T type from interface.
         * @param _object 
         * @param destroyer 
         * @return true 
         * @return false 
         */
        template <typename AT, typename DestroyFunctor>
        bool Erase(AT* _object, DestroyFunctor _destroyer);

        template <typename AT>
        bool Erase(AT* _object) { return Remove(_object, NoneFunctor<T>()); }


        template <typename DestroyFunctor>
        void Clear(DestroyFunctor _destroyer);

        void Clear() { Clear(NoneFunctor<T>()); }
    };
}

#include <SA/Engine/HI/InterfaceList.inl>

#endif // GUARD
