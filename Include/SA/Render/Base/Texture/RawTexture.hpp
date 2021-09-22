// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RAW_TEXTURE_GUARD
#define SAPPHIRE_RENDER_RAW_TEXTURE_GUARD

#include <SA/Core/Serialize/Serializer.hpp>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/Misc/Format.hpp>

namespace Sa
{
	struct RawTexture
	{
		Vec2ui extent;

		uint32 mipLevels = 1u;

		Format format = Format::RGBA_32;

		std::vector<char> data;


		// Compute original image size in format unit.
		uint64 GetMainSize() const noexcept;

		// Compute total image size (including mipmaps) in format unit.
		uint64 GetTotalSize() const noexcept;


		virtual void Reset();
	};


	namespace Serialize
	{
		void ToBinary(const RawTexture& _obj, std::string& _str);
		void FromBinary(RawTexture& _obj, Reader& _read);
	}
}

#endif // GUARD
