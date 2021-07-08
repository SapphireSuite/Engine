// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Axis/InputAxisContext.hpp>

namespace Sa
{
	void InputAxisContext::UnBind(Axis _axis)
	{
		auto it = mMap.find(_axis);

		if (it == mMap.end())
		{
			SA_LOG(L"Input key [" << _axis << "] not previously bound!", Warning, SA/Input);
			return;
		}

		mMap.erase(it);
	}

	void InputAxisContext::UnBind(std::shared_ptr<InputAxisBinding> _inBinding)
	{
		for (auto itBinds = mMap.begin(); itBinds != mMap.end(); ++itBinds)
		{
			for (auto it = itBinds->second.begin(); it != itBinds->second.end(); ++it)
			{
				if (_inBinding == *it)
					itBinds->second.erase(it--);
			}
		}
	}


	bool InputAxisContext::Process(const InputAxis& _inAxis)
	{
		auto itBinds = mMap.find(_inAxis.axis);

		// Action not bind.
		if (itBinds == mMap.end())
			return false;

		bool bRes = false;

		for (auto it = itBinds->second.begin(); it != itBinds->second.end(); ++it)
			bRes |= (*it)->Execute(_inAxis.value);

		return bRes;
	}
}
