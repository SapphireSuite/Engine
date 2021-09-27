// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/Base/Pipeline/PipelineShaderInfos.hpp>

namespace Sa
{
	void PipelineShaderInfos::AddShader(const AShader* _shader, const ShaderDescriptor& _descriptor)
	{
		if (_descriptor.stage == ShaderStage::Vertex)
			vertexBindingLayout.desiredLayout = VertexLayout::Make(static_cast<VertexComp>((uint8)_descriptor.vertexLayout)); // TODO: Clean.

		PipelineShaderStage& stage = stages.emplace_back();
		stage.shader = _shader;
		stage.stage = _descriptor.stage;
		stage.userSpecConstants = _descriptor.userSpecConstants;
		stage.engineSpecConstants = _descriptor.engineSpecConstants;


		// Bindings
		{
			for(uint32 i = 0; i < _descriptor.bindingSets.size(); ++i)
			{
				auto& setDesc = i < bindingSets.size() ? bindingSets[i] : bindingSets.emplace_back();

				for (auto& shBind : _descriptor.bindingSets[i].bindings)
				{
					bool bFound = false;

					// Search existing binding.
					for (auto& pipBind : setDesc.bindings)
					{
						if (shBind.binding == pipBind.binding)
						{
							pipBind.stageFlags |= _descriptor.stage;
							bFound = true;
							break;
						}
					}

					if (!bFound)
					{
						auto& pipBind = setDesc.bindings.emplace_back(shBind);
						pipBind.stageFlags = _descriptor.stage;
					}
				}
			}
		}

		/*
		// Spec constants.
		{
			// User
			for (auto& specCst : _descriptor.userSpecConstants)
			{
				bool bFound = false;

				for (auto& pipSpecCst : userSpecConstants)
				{
					if (specCst.id == pipSpecCst.id)
					{
						pipSpecCst.stageFlags |= _descriptor.stage;
						bFound = true;
						break;
					}
				}

				if (!bFound)
				{
					auto& pipSpecCst = userSpecConstants.emplace_back(specCst);
					pipSpecCst.stageFlags = _descriptor.stage;
				}
			}


			// Engine
			for (auto& specCst : _descriptor.engineSpecConstants)
			{
				bool bFound = false;

				for (auto& pipSpecCst : engineSpecConstants)
				{
					if (specCst.id == pipSpecCst.id)
					{
						pipSpecCst.stageFlags |= _descriptor.stage;
						bFound = true;
						break;
					}
				}

				if (!bFound)
				{
					auto& pipSpecCst = engineSpecConstants.emplace_back(specCst);
					pipSpecCst.stageFlags = _descriptor.stage;
				}
			}
		}
		*/
	}
}
