// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_HARDWARE_INTERFACE_GUARD
#define SAPPHIRE_ENGINE_HARDWARE_INTERFACE_GUARD

#include <SA/Support/Debug.hpp>

namespace Sa
{
	class HardwareInterface
	{
#if SA_DEBUG

		/// Ensure interface as been created / destroyed.
		bool bCreated = false;

#endif

	protected:

		/**
		*	Check if interface as been properly created (bCreated = true).
		*	Assertion thrown on failure.
		*/
		void CheckCreated() const;

	public:
		/**
		*	\brief Interface Destructor.
		*	Ensure Destroy as been called previously.
		*	Destrutor <b>non</b>-virtual. Inherit from this class to create a parent class.
		*/
		~HardwareInterface() noexcept(false);


		/**
		*	\brief Create and initialize this interface.
		*/
		virtual void Create();

		/**
		*	\brief Destroy this interface.
		*	Calls Clear().
		*/
		virtual void Destroy();

		/**
		*	\brief Clear all previously created/registered elements from this interface.
		*/
		virtual void Clear();
	};


// { Functor

    template <typename T>
    struct DestroyFunctor
    {
        void operator()(T& _in)
		{
			_in.Destroy();
		}
    };

//}

}

#endif // GUARD
