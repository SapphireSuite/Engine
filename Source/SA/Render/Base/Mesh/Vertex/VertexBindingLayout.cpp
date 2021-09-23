// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Mesh/Vertex/VertexBindingLayout.hpp>

namespace Sa
{
#if SA_VULKAN

	uint32 VertexBindingLayout::GetBindingDescriptionNum() const
	{
		return 1u;
	}

	uint32 VertexBindingLayout::GetAttributeDescriptionNum() const
	{
		// Prefer desired description.
		const VertexLayout* layout = desiredLayout ? desiredLayout.get() : meshLayout.get();

		SA_ASSERT(Nullptr, SA/Render, layout, L"Layout nullptr!");

		if (layout->comps == VertexComp::PNTanTex || layout->comps == VertexComp::PNTanC)
			return 4u;
		else if (layout->comps == VertexComp::PNTan || layout->comps == VertexComp::PNTex || layout->comps == VertexComp::PNC)
			return 3u;
		else if (layout->comps == VertexComp::PN || layout->comps == VertexComp::PTex || layout->comps == VertexComp::PC)
			return 2u;
		else if (layout->comps == VertexComp::Position)
			return 1u;

		return 0u;
	}

	std::unique_ptr<VkVertexInputBindingDescription> VertexBindingLayout::GetBindingDescription() const noexcept
	{
		// Only mesh layout can be bigger than desired.
		const VertexLayout* layout = meshLayout ? meshLayout.get() : desiredLayout.get();

		SA_ASSERT(Nullptr, SA/Render, layout, L"Layout nullptr!");

		uint32 size = layout->vertexSize;

		return std::make_unique<VkVertexInputBindingDescription>(VkVertexInputBindingDescription
		{
			0,										// binding.
			size,									// stride.
			VK_VERTEX_INPUT_RATE_VERTEX				// inputRate.
		});
	}

	std::unique_ptr<VkVertexInputAttributeDescription[]> VertexBindingLayout::GetAttributeDescriptions() const noexcept
	{
		// Prefer desired description.
		const VertexLayout* layout = desiredLayout ? desiredLayout.get() : meshLayout.get();

		SA_ASSERT(Nullptr, SA/Render, layout, L"Layout nullptr!");


		/** 
		*	Layout to check offset.
		*	Adapt offset binding from mesh if provided.
		*/
		const VertexLayout* const offsetLayout = meshLayout ? meshLayout.get() : desiredLayout.get();

		uint32 index = 0u;
		std::unique_ptr<VkVertexInputAttributeDescription[]> result(new VkVertexInputAttributeDescription[GetAttributeDescriptionNum()]);

		if (layout->comps & VertexComp::Position)
		{
			SA_ASSERT(Default, SA/Render, offsetLayout->comps & VertexComp::Position, L"Try bind a missing component in mesh layout!");

			result[index++] =
			{
				0,									// location.
				0,									// binding.
				VK_FORMAT_R32G32B32_SFLOAT,			// format.
				offsetLayout->GetPositionOffet()	// offset
			};
		}

		if (layout->comps & VertexComp::Normal)
		{
			SA_ASSERT(Default, SA/Render, offsetLayout->comps & VertexComp::Normal, L"Try bind a missing component in mesh layout!");

			result[index++] =
			{
				1,									// location.
				0,									// binding.
				VK_FORMAT_R32G32B32_SFLOAT,			// format.
				offsetLayout->GetNormalOffet()		// offset
			};
		}

		if (layout->comps & VertexComp::Tangent)
		{
			SA_ASSERT(Default, SA/Render, offsetLayout->comps & VertexComp::Tangent, L"Try bind a missing component in mesh layout!");

			result[index++] =
			{
				2,									// location.
				0,									// binding.
				VK_FORMAT_R32G32B32_SFLOAT,			// format.
				offsetLayout->GetTangentOffet()		// offset
			};
		}

		if (layout->comps & VertexComp::Texture)
		{
			SA_ASSERT(Default, SA/Render, offsetLayout->comps & VertexComp::Texture, L"Try bind a missing component in mesh layout!");

			result[index++] =
			{
				3,									// location.
				0,									// binding.
				VK_FORMAT_R32G32_SFLOAT,			// format.
				offsetLayout->GetTextureOffet()		// offset
			};
		}

		if (layout->comps & VertexComp::Color)
		{
			SA_ASSERT(Default, SA/Render, offsetLayout->comps & VertexComp::Color, L"Try bind a missing component in mesh layout!");

			result[index++] =
			{
				4,									// location.
				0,									// binding.
				VK_FORMAT_R32G32B32_SFLOAT,			// format.
				offsetLayout->GetColorOffet()		// offset
			};
		}


		return result;
	}

#endif
}
