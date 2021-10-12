// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ACAMERA_GUARD
#define SAPPHIRE_RENDER_ACAMERA_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Maths/Transform/Transform.hpp>
#include <SA/Render/Base/Camera/CameraUBO.hpp>

namespace Sa
{
	class ARenderDevice;

	class ACamera : public Abstract
	{
	protected:
		CameraUBO mUBOData;

		bool bProjDirty = false;
		bool bTransformDirty = false;

	public:
		virtual void Create(const ARenderDevice* _device) = 0;
		virtual void Destroy(const ARenderDevice* _device) = 0;

		virtual void Update(const ARenderDevice* _device) = 0;


		const CMat4f& GetProjection() const noexcept;
		void SetProjection(const CMat4f& _proj) noexcept;

		void SetTransform(const TransffPR& _tr);
	};
}

#endif // GUARD