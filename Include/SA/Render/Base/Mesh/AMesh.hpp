// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_AMESH_GUARD
#define SAPPHIRE_RENDER_AMESH_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Base/Mesh/RawMesh.hpp>
#include <SA/Render/Base/Mesh/MeshDrawInfos.hpp>

namespace Sa
{
	class ARenderFrame;
	class ARenderDevice;
	class ARenderResourceInitializer;

	class AMesh : public Abstract
	{
	protected:
		std::shared_ptr<VertexLayout> mLayout;

	public:
		std::shared_ptr<VertexLayout> GetLayout() const noexcept;

		virtual void Create(ARenderResourceInitializer* _init, const RawMesh& _raw);
		virtual void Destroy(const ARenderDevice* _device) = 0;

		virtual void Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos = MeshDrawInfos()) const = 0;
	};
}

#endif // GUARD
