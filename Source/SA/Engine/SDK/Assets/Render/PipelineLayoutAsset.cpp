// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/PipelineLayoutAsset.hpp>

namespace SA::SDK
{
	bool PipelineLayoutAsset::IsValid() const
	{
		return descriptor.Empty();
	}


	bool PipelineLayoutAsset::Load_Internal(std::string&& _bin)
	{
		Ser::BinaryStream ser(std::move(_bin));

		ser >> descriptor;

		return true;
	}
	
	void PipelineLayoutAsset::UnLoad()
	{
		return descriptor.Clear();
	}


	bool PipelineLayoutAsset::Save_Internal(std::fstream& _fstream) const
	{
		Ser::BinaryStream ser;

		ser << descriptor;

		_fstream << ser.bin;

		return true;
	}
}
