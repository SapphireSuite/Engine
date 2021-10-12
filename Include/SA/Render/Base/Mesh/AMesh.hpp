// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_AMESH_GUARD
#define SAPPHIRE_RENDER_AMESH_GUARD

#include <SA/Render/Base/ARenderResource.hpp>

#include <SA/Render/Base/Mesh/RawMesh.hpp>
#include <SA/Render/Base/Mesh/MeshDrawInfos.hpp>

namespace Sa
{
	class ARenderFrame;

	class AMesh : public ARenderResource
	{
	protected:
		std::shared_ptr<VertexLayout> mLayout;

	public:
		std::shared_ptr<VertexLayout> GetLayout() const noexcept;

		virtual void Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos = MeshDrawInfos()) const = 0;
	};
}

#endif // GUARD
