// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename InputT>
	bool IInputSystem::Process(const InputT& _input)
	{
		// Process from last added context to older one.

		bool bSuccess = false;

		for (auto it = mContexts.rbegin(); it != mContexts.rend(); ++it)
		{
			if ((*it)->Process(_input))
			{
				bSuccess = true;

				// Consume input (no forward to next contexts).
				if ((*it)->mode == InputContext::ProcessMode::Consume)
					return true;
			}
		}

		return bSuccess;
	}
}
