// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/MaterialBuilder/Nodes/Operators/MaterialNodeOp.hpp>

#include <SA/Collections/Debug>

namespace SA::SDK
{
	MaterialNodeOp::MaterialNodeOp(std::vector<std::shared_ptr<MaterialNodeInput>> _inputs) : 
		mInputs{ std::move(_inputs) }
	{
	}


	void MaterialNodeOp::AddEntry(std::shared_ptr<MaterialNodeInput> _input, uint32_t _pos)
	{
		auto it = mInputs.end();

		if(_pos != ~uint32_t())
		{
			SA_ASSERT(OutOfArrayRange, SA/Engine/SDK/MaterialBuilder, _pos, mInputs);

			it = mInputs.begin() + _pos;
		}

		mInputs.insert(it, _input);
	}
	
	void MaterialNodeOp::RemoveEntry(std::shared_ptr<MaterialNodeInput> _input, bool bRemoveAllInstance)
	{
		for(auto it = mInputs.begin(); it != mInputs.end();)
		{
			if (*it == _input)
			{
				it = mInputs.erase(it);

				if(!bRemoveAllInstance)
					return;
			}
			else
				it++;
		}
	}
	
	void MaterialNodeOp::RemoveEntry(uint32_t _pos)
	{
		SA_ASSERT(OutOfArrayRange, SA/Engine/SDK/MaterialBuilder, _pos, mInputs);

		mInputs.erase(mInputs.begin() + _pos);
	}


	MaterialNodeOp::InputIterator MaterialNodeOp::begin()
	{
		return mInputs.begin();
	}
	
	MaterialNodeOp::InputIterator MaterialNodeOp::end()
	{
		return mInputs.end();
	}
}