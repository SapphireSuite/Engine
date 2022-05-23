// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_VERTEX_LOCATION_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_VERTEX_LOCATION_DESCRIPTOR_GUARD

#include <SA/Engine/Render/Base/Misc/Format.hpp>

#include <SA/Engine/Render/Base/Mesh/Vertex/Vertex.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderVertexLocationDescriptor.hpp>

namespace SA
{
	struct PipelineVertexLocationDescriptor : public ShaderVertexLocationDescriptor
	{
		/// Bound component offset. Set by BindVertexComponent.
		uint32_t componentOffset = 0u;

		/// Bound component format. Set by BindVertexComponent.
		Format format;

		template <typename VertexT, typename VertexCompT>
		void BindVertexComponent()
		{
			format = VertexCompT::format;
			componentOffset = VertexT::template GetComponentOffset<VertexCompT>();
		}

		PipelineVertexLocationDescriptor(const ShaderVertexLocationDescriptor& _shDesc) :
			ShaderVertexLocationDescriptor(_shDesc)
		{
		}
	};
}

#endif // GUARD
