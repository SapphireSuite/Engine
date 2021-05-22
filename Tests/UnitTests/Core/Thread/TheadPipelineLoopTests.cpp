// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Thread/Pipeline/ThreadPipeline.hpp>
using namespace Sa;

namespace Sa::TheadPipelineLoop_UT
{
#if !SA_CI
#define LOG(...) SA_LOG(__VA_ARGS__)
#else
#define LOG(...) {}
#endif

	ThreadPipeline thPipeline;

	using Data = uint32;

	uint32 gID = 0;
	auto createDataFunctor = []() { return new Data{ gID++ }; };
	auto deleteDataFunctor = [](void* _buff) { delete static_cast<Data*>(_buff); };
	void DataCopy(const void* _src, void* _dst) { *static_cast<Data*>(_dst) = *static_cast<const Data*>(_src); }

	uint32 behSubmit = 0;
	void BehaviorUpdate(ThreadState& _state)
	{
		_state.CreateBuffers(createDataFunctor, createDataFunctor);

		while (_state.Submit())
		{
			// Must get after each submit.
			const Data* in = _state.GetInputBuffer<Data>();
			LOG("BH.in: " << *in);

			Data* out = _state.GetOutputBuffer<Data>();
			Data rand = UTH::Rand(0u, 100u);
			LOG("BH.out: " << *out << " -> " << rand);
			*out = rand;
			
			++behSubmit;
		}

		_state.DestroyBuffers(deleteDataFunctor, deleteDataFunctor);
	}

	uint32 phSubmit = 0;
	void PhysicsUpdate(ThreadState& _state)
	{
		_state.CreateBuffers(createDataFunctor, createDataFunctor);

		while (_state.Submit())
		{
			// Must get after each submit.
			const Data* in = _state.GetInputBuffer<Data>();
			LOG("PH.in: " << *in);

			Data* out = _state.GetOutputBuffer<Data>();
			Data rand = UTH::Rand(0u, 100u);
			LOG("PH.out: " << *out << " -> " << rand);
			*out = rand;

			++phSubmit;
		}

		_state.DestroyBuffers(deleteDataFunctor, deleteDataFunctor);
	}

	uint32 rendSubmit = 0;
	void RenderUpdate(ThreadState& _state)
	{
		_state.CreateBuffers(createDataFunctor, createDataFunctor);

		while (_state.Submit())
		{
			// Must get after each submit.
			const Data* in = _state.GetInputBuffer<Data>();
			LOG("RN.in: " << *in);

			Data* out = _state.GetOutputBuffer<Data>();
			Data rand = UTH::Rand(0u, 100u);
			LOG("RN.out: " << *out << " -> " << rand);
			*out = rand;

			++rendSubmit;
		}

		_state.DestroyBuffers(deleteDataFunctor, deleteDataFunctor);
	}

	bool Create()
	{
		ThreadPipeline::CreateInfos thPipeInfos;

		// Behavior Step.
		{
			ThreadAttachment::CreateInfos& infos = thPipeInfos.attachInfos.emplace_back();

			infos.main = BehaviorUpdate;
			infos.inAttachIndex = 2;	// Render Step.
			infos.stateInfos.frequency = 1.0f / 30.0f;
			infos.stateInfos.queryMode = ThreadState::QueryMode::Move;
		}

		// Physics Step.
		{
			ThreadAttachment::CreateInfos& infos = thPipeInfos.attachInfos.emplace_back();

			infos.main = PhysicsUpdate;
			infos.inAttachIndex = 0;	// Behavior Step.
			infos.stateInfos.frequency = 1.0f / 120.0f;
			infos.stateInfos.copyBuffer = DataCopy;
			infos.stateInfos.inputState = ThreadState::InputState::SelfSubmit;
			infos.stateInfos.queryMode = ThreadState::QueryMode::Move;
		}

		// Render Step.
		{
			ThreadAttachment::CreateInfos& infos = thPipeInfos.attachInfos.emplace_back();

			infos.main = RenderUpdate;
			infos.inAttachIndex = 1;	// Physics Step.
			infos.stateInfos.frequency = 1.0f / 60.0f;
			infos.stateInfos.copyBuffer = DataCopy;
			infos.stateInfos.queryMode = ThreadState::QueryMode::Copy;
		}

		thPipeline.Create(std::move(thPipeInfos));

		return true;
	}

	bool Start()
	{
		thPipeline.Start();

		return true;
	}

	bool Update()
	{
		float gTime = 0.0f;
#if SA_CI
		const float maxTime = 2.0f;
#else
		const float maxTime = 1.0f / 30.0f;
#endif

		auto start = std::chrono::steady_clock::now();

		while (gTime < maxTime)
		{
			auto end = std::chrono::steady_clock::now();

			float deltaTime = std::chrono::duration<float>(end - start).count();
			gTime += deltaTime;

			thPipeline.Update(deltaTime);

			start = end;
		}

		return true;
	}

	bool End()
	{
		thPipeline.End();

		SA_LOG(L"Behavior Submit: " << behSubmit);
		SA_LOG(L"Physics Submit: " << phSubmit);
		SA_LOG(L"Render Submit: " << rendSubmit);

		return true;
	}

	bool Destroy()
	{
		thPipeline.Destroy();

		return true;
	}
}

void TheadPipelineLoopTests()
{
	using namespace TheadPipelineLoop_UT;

	SA_UTH_SF(Create);
	SA_UTH_SF(Start);
	SA_UTH_SF(Update);
	SA_UTH_SF(End);
	SA_UTH_SF(Destroy);
}
