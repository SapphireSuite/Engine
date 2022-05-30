// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/RenderPassAsset.hpp>

namespace SA::SDK
{
	bool RenderPassAsset::IsValid() const
	{
		return !descriptor.subPassDescs.empty();
	}


	bool RenderPassAsset::Load_Internal(std::string&& _bin)
	{
		Ser::BinaryStream ser(std::move(_bin));

		ser >> descriptor;

		return true;
	}

	void RenderPassAsset::UnLoad()
	{
		descriptor.Clear();
	}


	bool RenderPassAsset::Save_Internal(std::fstream& _fstream) const
	{
		Ser::BinaryStream ser;

		ser << descriptor;

		_fstream << ser.bin;

		return true;
	}
}
