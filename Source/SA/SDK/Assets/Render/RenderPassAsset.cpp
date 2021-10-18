// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/RenderPassAsset.hpp>

#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
	bool RenderPassAsset::IsValid() const
	{
		return !raw.subPassDescs.empty();
	}


	bool RenderPassAsset::Load_Internal(Serialize::Reader&& _read, const std::string& _path)
	{
		(void)_path;

		Serialize::FromBinary(raw, _read);

		return true;
	}
	
	void RenderPassAsset::UnLoad()
	{
		raw.subPassDescs.clear();
	}


	bool RenderPassAsset::Save_Internal(std::fstream& _fStream) const
	{
		_fStream << Serialize::ToBinary(raw);

		return true;
	}
	
	bool RenderPassAsset::Import_Internal(const std::string& _path)
	{
		(void)_path;

		return false;
	}
}
