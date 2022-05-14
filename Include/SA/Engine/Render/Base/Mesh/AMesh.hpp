// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AMESH_GUARD
#define SAPPHIRE_ENGINE_AMESH_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Render/Base/Mesh/RawMesh.hpp>
#include <SA/Engine/Render/Base/Mesh/MeshDrawInfos.hpp>

namespace SA
{
	struct ARenderFrame;

	class AMesh : protected HardwareInterface
	{
		using HardwareInterface::Clear; // not used.

		virtual void Draw(const ARenderFrame& _frame, const MeshDrawInfos& _infos = MeshDrawInfos()) const = 0;
	};
}

#endif // GUARD
