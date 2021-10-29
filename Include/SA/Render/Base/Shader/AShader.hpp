// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma	once

#ifndef SAPPHIRE_RENDER_ASHADER_GUARD
#define SAPPHIRE_RENDER_ASHADER_GUARD

#include <SA/Core/Types/Variadics/SparseVector.hpp>

#include <SA/Render/Base/Shader/RawShader.hpp>

namespace Sa
{
	class AShader
	{
	};

	using ShaderHandle = SparseVectorHandle<AShader>;
}

#endif // GUARD
