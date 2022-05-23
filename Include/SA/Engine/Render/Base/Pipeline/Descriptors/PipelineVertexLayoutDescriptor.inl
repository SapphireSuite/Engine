// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

namespace SA
{
	template <typename VertexT, typename FirstT, typename... Args>
	void PipelineVertexLayoutDescriptor::BindVertexComponentsPacked(uint32_t _offset)
	{
		SA_ASSERT(OutOfRange, SA/Engine/Render, _offset, 0u, locations.size(), L"Too much Vertex Component to bind provided.");

		locations[_offset].BindVertexComponent<VertexT, FirstT>();

		if constexpr (sizeof...(Args) != 0)
			BindVertexComponentsPacked<VertexT, Args...>(++_offset);
	}

	template <typename VertexT, typename... Args>
	void PipelineVertexLayoutDescriptor::BindVertexComponents()
	{
		vertexSize = sizeof(VertexT);

		BindVertexComponentsPacked<VertexT, Args...>(0u);
	}
}
