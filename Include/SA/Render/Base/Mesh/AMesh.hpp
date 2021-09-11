// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_AMESH_GUARD
#define SAPPHIRE_RENDER_AMESH_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Base/Mesh/RawMesh.hpp>

namespace Sa
{
	class AMesh : public Abstract
	{
	protected:
		std::shared_ptr<VertexLayout> mLayout;

	public:
		std::shared_ptr<VertexLayout> GetLayout() const noexcept;

		void Create(const RawMesh& _rawMesh);
	};
}

#endif // GUARD
