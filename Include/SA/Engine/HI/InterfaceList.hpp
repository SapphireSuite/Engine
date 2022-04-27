// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_INTERFACE_LIST_GUARD
#define SAPPHIRE_ENGINE_INTERFACE_LIST_GUARD

#include <forward_list>

namespace Sa
{
    template <typename T>
    class InterfaceList
    {
        std::forward_list<T> mObjects;

    public:
        using DestroyerT = void (*)(T&);

        static const DestroyerT defaultDestroyer;


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
        template <typename AT>
        bool Remove(AT* _object, DestroyerT destroyer = defaultDestroyer);

        void Clear(DestroyerT destroyer = defaultDestroyer);
    };
}

#include <SA/Engine/HI/InterfaceList.inl>

#endif // GUARD
