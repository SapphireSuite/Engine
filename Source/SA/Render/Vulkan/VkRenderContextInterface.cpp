// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderContextInterface.hpp>
#include <Render/Vulkan/VkRenderGraphicInterface.hpp>

#include <Core/Algorithms/Cast.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/Surface/VkWindowSurface.hpp>
//#include <Render/Vulkan/Pipeline/VkPipeline.hpp>

//#include <Render/Vulkan/Camera/VkCamera.hpp>

namespace Sa::Vk
{
	void RenderContextInterface::Create(const RenderGraphicInterface* _graphics)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _graphics);

		mGraphics = _graphics;

		mMeshVertexHeap.Create(GetDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 1024);
		mMeshIndicesHeap.Create(GetDevice(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, 1024);

		SA_LOG(L"Render Context Interface created.", Infos, SA/Render/Vulkan);
	}

	void RenderContextInterface::Destroy()
	{
		// Destroy in reversed order.
		{
			while (!mPipelines.empty())
				DestroyPipeline(&mPipelines.front());

			while (!mCubemaps.empty())
				DestroyCubemap(&mCubemaps.front());

			while (!mTextures.empty())
				DestroyTexture(&mTextures.front());

			while (!mStaticMeshes.empty())
				DestroyStaticMesh(&mStaticMeshes.front());

			while (!mShaders.empty())
				DestroyShader(&mShaders.front());

			while (!mResInits.empty())
				DestroyResourceInitializer(&mResInits.front());

			while (!mRenderPasses.empty())
				DestroyRenderPass(&mRenderPasses.front());

			while (!mSurfaces.empty())
				DestroySurface(&mSurfaces.front());
		}

		mMeshVertexHeap.Destroy(GetDevice());
		mMeshIndicesHeap.Destroy(GetDevice());

		mGraphics = nullptr;

		SA_LOG(L"Render Context  Interface destroyed.", Infos, SA/Render/Vulkan);
	}


	const Device& RenderContextInterface::GetDevice() const
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, mGraphics);

		return mGraphics->device;
	}

	
	ARenderSurface* RenderContextInterface::CreateSurface(AWindowSurface* _winSurface)
	{
		Surface& surface = mSurfaces.emplace_front();

		surface.Create(GetDevice(), CastRef<WindowSurface>(_winSurface));

		return &surface;
	}

	void RenderContextInterface::DestroySurface(ARenderSurface* _surface)
	{
		Surface& vkSurface = CastRef<Surface>(_surface);

		if (vkSurface.FrameBuffersValid())
			DestroyFrameBuffers(_surface);

		vkSurface.Destroy(GetDevice());

		mSurfaces.remove(vkSurface);
	}


	ARenderPass* RenderContextInterface::CreateRenderPass(const RenderPassDescriptor& _descriptor)
	{
		RenderPass& pass = mRenderPasses.emplace_front();

		pass.Create(GetDevice(), _descriptor);

		return &pass;
	}
	
	void RenderContextInterface::DestroyRenderPass(ARenderPass* _pass)
	{
		RenderPass& vkPass = CastRef<RenderPass>(_pass);

		vkPass.Destroy(GetDevice());

		mRenderPasses.remove(vkPass);
	}


	void RenderContextInterface::CreateFrameBuffers(ARenderSurface* _surface, ARenderPass* _pass, const RenderPassDescriptor& _descriptor)
	{
		CastRef<Surface>(_surface).CreateFrameBuffers(GetDevice(), CastRef<RenderPass>(_pass), _descriptor);
	}

	void RenderContextInterface::DestroyFrameBuffers(ARenderSurface* _surface)
	{
		CastRef<Surface>(_surface).DestroyFrameBuffers(GetDevice());
	}


//{ Resources

	ARenderPipeline* RenderContextInterface::CreatePipeline(const RenderPipelineDescriptor& _desc)
	{
		Pipeline& pipline = mPipelines.emplace_front();

		// TODO.
		//pipline.Create(GetDevice(), _desc);

		return &pipline;
	}

	void RenderContextInterface::DestroyPipeline(ARenderPipeline* _pipeline)
	{
		Pipeline& vkPipline = CastRef<Pipeline>(_pipeline);

		// TODO.
		//vkPipline.Destroy(GetDevice());

		mPipelines.remove(vkPipline);
	}


	ARenderResourceInitializer* RenderContextInterface::CreateResourceInitializer()
	{
		ResourceInitializer& init = mResInits.emplace_front();

		init.Create(GetDevice());

		return &init;
	}

	void RenderContextInterface::DestroyResourceInitializer(ARenderResourceInitializer* _init)
	{
		ResourceInitializer& vkInit = CastRef<ResourceInitializer>(_init);

		vkInit.Destroy(GetDevice());

		mResInits.remove(vkInit);
	}

	void RenderContextInterface::SubmitResourceInitializer(ARenderResourceInitializer* _init)
	{
		ResourceInitializer& vkInit = CastRef<ResourceInitializer>(_init);

		vkInit.Submit(GetDevice());
	}


	AShader* RenderContextInterface::CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw)
	{
		Shader& shader = mShaders.emplace_front();

		ResourceInitializer& vkInit = CastRef<ResourceInitializer>(_init);

		shader.Create(GetDevice(), vkInit, _raw);

		return &shader;
	}

	void RenderContextInterface::DestroyShader(AShader* _shader)
	{
		Shader& vkShader = CastRef<Shader>(_shader);

		vkShader.Destroy(GetDevice());

		mShaders.remove(vkShader);
	}


	AStaticMesh* RenderContextInterface::CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw)
	{
		BLStaticMesh& mesh = mStaticMeshes.emplace_front();

		ResourceInitializer& vkInit = CastRef<ResourceInitializer>(_init);

		mesh.Create(GetDevice(), vkInit, mMeshVertexHeap, mMeshIndicesHeap, _raw);
		
		return &mesh;
	}
	
	void RenderContextInterface::DestroyStaticMesh(AStaticMesh* _mesh)
	{
		BLStaticMesh& vkMesh = CastRef<BLStaticMesh>(_mesh);

		vkMesh.Destroy(GetDevice(), mMeshVertexHeap, mMeshIndicesHeap);

		mStaticMeshes.remove(vkMesh);
	}


	ATexture* RenderContextInterface::CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw)
	{
		Texture& texture = mTextures.emplace_front();

		ResourceInitializer& vkInit = CastRef<ResourceInitializer>(_init);

		texture.Create(GetDevice(), vkInit, _raw);

		return &texture;
	}
	
	void RenderContextInterface::DestroyTexture(ATexture* _texture)
	{
		Texture& vkTexture = CastRef<Texture>(_texture);

		vkTexture.Destroy(GetDevice());

		mTextures.remove(vkTexture);
	}

	
	ACubemap* RenderContextInterface::CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw)
	{
		Cubemap& cubemap = mCubemaps.emplace_front();
		
		ResourceInitializer& vkInit = CastRef<ResourceInitializer>(_init);

		cubemap.Create(GetDevice(), vkInit, _raw);

		return &cubemap;
	}
	
	void RenderContextInterface::DestroyCubemap(ACubemap* _cubemap)
	{
		Cubemap& vkCubemap = CastRef<Cubemap>(_cubemap);

		vkCubemap.Destroy(GetDevice());

		mCubemaps.remove(vkCubemap);
	}


	//ACamera* RenderContextInterface::CreateCamera()
	//{
	//	Camera* const camera = new Camera();

	//	camera->Create(mDevice);

	//	return camera;
	//}
	//
	//void RenderContextInterface::DestroyCamera(ACamera* _camera)
	//{
	//	Camera* const vkCamera = _camera->AsPtr<Camera>();

	//	vkCamera->Destroy(mDevice);

	//	delete vkCamera;
	//}

//}
}
