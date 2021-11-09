// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Mesh/VkMeshMgr.hpp>

#include <Collections/Debug>

#include <Maths/Matrix/Matrix3.hpp>
#include <Maths/Matrix/Matrix4.hpp>

namespace Sa::Vk
{
	constexpr uint64 gBufferHeapDefaultSize = 1024;
	constexpr uint64 gFrameBufferDefaultElemNum = 10;
	constexpr VkBufferUsageFlagBits gBufferUsage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
	constexpr VkDescriptorType gBufferDescriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

	void MeshMgr::Create(const Device& _device, uint32 _frameNum)
	{
		// Buffers
		{
			mVertexHeap.Create(_device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, gBufferHeapDefaultSize);
			mIndicesHeap.Create(_device, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, gBufferHeapDefaultSize);


			mFrames.resize(_frameNum);

			for (auto& frame : mFrames)
			{
				frame.transformBuffer.Create(_device, gBufferUsage, gFrameBufferDefaultElemNum * sizeof(Mat4f));
				frame.normalBuffer.Create(_device, gBufferUsage, gFrameBufferDefaultElemNum * sizeof(Mat3f));
			}
		}


		// Descriptor Sets.
		{
			// TODO: Remove later.
			PipelineBindingSetDescriptor modelBindSetDesc;
			auto& trBind = modelBindSetDesc.bindings.emplace_back();
			trBind.binding = 0u;
			trBind.type = ShaderBindingType::StorageBuffer;
			trBind.stageFlags = ShaderStage::Vertex;

			auto& normalBind = modelBindSetDesc.bindings.emplace_back();
			normalBind.binding = 1u;
			normalBind.type = ShaderBindingType::StorageBuffer;
			normalBind.stageFlags = ShaderStage::Vertex;
			//

			mDescriptorPool.Create(_device, modelBindSetDesc, _frameNum);
			mDescriptorSetLayout.Create(_device, modelBindSetDesc);

			mDescriptorSets = mDescriptorPool.Allocate(_device, std::vector<DescriptorSetLayout>(_frameNum, mDescriptorSetLayout));


			// Bind buffer to descriptor.
			for (uint32 i = 0; i < _frameNum; ++i)
			{
				DescriptorSet::Updater updater = mDescriptorSets[i].MakeUpdater();

				updater.Add(modelBindSetDesc.bindings[0].binding, { &mFrames[i].transformBuffer }, gBufferDescriptorType);
				updater.Add(modelBindSetDesc.bindings[1].binding, { &mFrames[i].normalBuffer }, gBufferDescriptorType);

				updater.Submit(_device);
			}
		}


		SA_LOG(L"Mesh Manager created.", Infos, SA/Render/Vulkan);
	}

	void MeshMgr::Destroy(const Device& _device)
	{
		// Descriptor Sets.
		{
			// Not needed: Auto free on destroy.
			//mDescriptorPool.Free(_device, mDescriptorSets);

			mDescriptorPool.Destroy(_device);
			mDescriptorSetLayout.Destroy(_device);

			mDescriptorSets.clear();
		}


		// Buffers
		{
			mVertexHeap.Destroy(_device);
			mIndicesHeap.Destroy(_device);


			for (auto& frame : mFrames)
			{
				frame.transformBuffer.Destroy(_device);
				frame.normalBuffer.Destroy(_device);
			}

			mFrames.clear();
		}


		SA_LOG(L"Mesh Manager destroyed.", Infos, SA/Render/Vulkan);
	}


	BLStaticMesh* MeshMgr::CreateStaticMesh(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw)
	{
		BLStaticMesh& mesh = mStaticMeshes.emplace_front();

		mesh.Create(_device, _init, mVertexHeap, mIndicesHeap, _raw);

		return &mesh;
	}

	void MeshMgr::DestroyStaticMesh(const Device& _device, BLStaticMesh* _mesh)
	{
		SA_ASSERT(Nullptr, Sa/Render/Vulkan, _mesh);

		_mesh->Destroy(_device, mVertexHeap, mIndicesHeap);

		mStaticMeshes.remove(*_mesh);
	}
}
