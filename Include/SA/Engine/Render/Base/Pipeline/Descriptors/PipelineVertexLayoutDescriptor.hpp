// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_ENGINE_PIPELINE_VERTEX_LAYOUT_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_VERTEX_LAYOUT_DESCRIPTOR_GUARD

#include <vector>

#include <SA/Collections/Debug>

#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelineVertexLocationDescriptor.hpp>

namespace SA
{
	struct ShaderVertexLayoutDescriptor;

	struct PipelineVertexLayoutDescriptor
	{
		/// Bound vertex size. Set by BindVertexComponents.
		uint32_t vertexSize = 0u;

		std::vector<PipelineVertexLocationDescriptor> locations;

		template <typename VertexT, typename... Args>
		void BindVertexComponents();

		PipelineVertexLayoutDescriptor& operator=(const ShaderVertexLayoutDescriptor& _shDesc);

	private:
		template <typename VertexT, typename FirstT, typename... Args>
		void BindVertexComponentsPacked(uint32_t _offset);
	};
}

#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelineVertexLayoutDescriptor.inl>

#endif // GUARD
