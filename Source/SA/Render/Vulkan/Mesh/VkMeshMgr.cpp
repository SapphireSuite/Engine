// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Mesh/VkMeshMgr.hpp>

#include <Collections/Debug>

#include <Core/Algorithms/SizeOf.hpp>

namespace Sa::Vk
{
	constexpr uint64 gBufferHeapDefaultSize = 1024;
	constexpr uint64 gFrameBufferDefaultElemNum = 10;
	constexpr VkBufferUsageFlagBits gBufferUsage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;

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


		ResourceMgr::Create(_device, PipelineBindingSetDescriptor::modelBindSetDesc, _frameNum);


		SA_LOG(L"Mesh Manager created.", Infos, SA/Render/Vulkan);
	}

	void MeshMgr::Destroy(const Device& _device)
	{
		ResourceMgr::Destroy(_device);


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


	void MeshMgr::FillDescriptorUpdater(DescriptorSet::Updater& _updater, uint32 _frame)
	{
		// TODO: Clean hard code.
		_updater.Add(0u, { &mFrames[_frame].transformBuffer });
		_updater.Add(1u, { &mFrames[_frame].normalBuffer });
	}


	void MeshMgr::Update(const Device& _device,
		const std::vector<CMat4f>& _transforms,
		const std::vector<CMat3f>& _normals,
		uint32 _frame)
	{
		SA_ASSERT(OutOfRange, SA/Render/Vulkan, _frame, 0u, (uint32)mFrames.size());

		Frame& frame = mFrames[_frame];

		UpdateBuffer(_device, frame.transformBuffer, 0u, _transforms.data(), OctSizeOf<uint64>(_transforms), _frame);
		UpdateBuffer(_device, frame.normalBuffer, 1u, _normals.data(), OctSizeOf<uint64>(_normals), _frame);
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
