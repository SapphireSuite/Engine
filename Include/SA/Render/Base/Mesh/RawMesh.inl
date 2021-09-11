// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <VertexComp inComps>
	void RawMesh::SetLayout()
	{
		// No conversion to perform.
		if (mLayout->comps == VertexComp::None || mLayout->comps == _comps || vertices.empty())
		{
			mLayout = VertexLayout::Make<inComps>();
			return;
		}

		// TODO: Implement layout conversion.
		SA_ASSERT(Default, SA/Render, false, L"Method not implemented yet!");

		mLayout = VertexLayout::Make<inComps>();
	}


	template <VertexComp Comps>
	RawMesh RawMesh::Triangle() noexcept
	{
		RawMesh mesh;

		mesh.mLayout = VertexLayout::Make<Comps>();

		const Vertex<Comps> vertices[] =
		{
			Vertex<VertexComp::PNTanTex>{
				Vec3f{ 0.0f, 0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.5f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{
				Vec3f{ 0.5f, -0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
			},

			Vertex<VertexComp::PNTanTex>{
				Vec3f{ -0.5f, -0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
			},
		};

		constexpr uint32 totalSize = SizeOf<uint32>(vertices) * sizeof(Vertex<Comps>);

		mesh.vertices.resize(totalSize);
		MemMove(reinterpret_cast<const char*>(vertices), mesh.vertices.data(), totalSize);

		mesh.indices = { 0, 1, 2 };

		if constexpr (Comps & VertexComp::Tangent)
			mesh.ComputeTangents();

		return mesh;
	}

	template <VertexComp Comps>
	RawMesh RawMesh::Square() noexcept
	{
		RawMesh mesh;

		mesh.mLayout = VertexLayout::Make<Comps>();

		const Vertex<Comps> vertices[] =
		{
			Vertex<VertexComp::PNTanTex>{
				Vec3f{ -0.5f, 0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{
				Vec3f{ 0.5f, 0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{
				Vec3f{ 0.5f, -0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
			},

			Vertex<VertexComp::PNTanTex>{
				Vec3f{ -0.5f, -0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
			},
		};

		constexpr uint32 totalSize = SizeOf<uint32>(vertices) * sizeof(Vertex<Comps>);

		mesh.vertices.resize(totalSize);
		MemMove(reinterpret_cast<const char*>(vertices), mesh.vertices.data(), totalSize);

		mesh.indices = { 0, 1, 2, 2, 3, 0 };

		if constexpr (Comps & VertexComp::Tangent)
			mesh.ComputeTangents();

		return mesh;
	}

	template <VertexComp Comps>
	RawMesh RawMesh::Cube() noexcept
	{
		RawMesh mesh;

		mesh.mLayout = VertexLayout::Make<Comps>();

		const Vertex<Comps> vertices[] =
		{
			// Front face.
			Vertex<VertexComp::PNTanTex>{											// 0.
				Vec3f{ -0.5f, 0.5f, 0.5f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 1.
				Vec3f{ 0.5f, 0.5f, 0.5f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 2.
				Vec3f{ 0.5f, -0.5f, 0.5f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 3.
				Vec3f{ -0.5f, -0.5f, 0.5f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
			},


			// Right face.
			Vertex<VertexComp::PNTanTex>{											// 4.
				Vec3f{ 0.5f, 0.5f, 0.5f },
				Vec3f::Right,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 5.
				Vec3f{ 0.5f, 0.5f, -0.5f },
				Vec3f::Right,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 6.
				Vec3f{ 0.5f, -0.5f, -0.5f },
				Vec3f::Right,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 7.
				Vec3f{ 0.5f, -0.5f, 0.5f },
				Vec3f::Right,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
			},


			// Back face.
			Vertex<VertexComp::PNTanTex>{											// 8
				Vec3f{ 0.5f, 0.5f, -0.5f },
				-Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 9.
				Vec3f{ -0.5f, 0.5f, -0.5f },
				-Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 10.
				Vec3f{ -0.5f, -0.5f, -0.5f },
				-Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 11.
				Vec3f{ 0.5f, -0.5f, -0.5f },
				-Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
			},


			// Left face.
			Vertex<VertexComp::PNTanTex>{											// 12.
				Vec3f{ -0.5f, 0.5f, -0.5f },
				-Vec3f::Right,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 13.
				Vec3f{ -0.5f, 0.5f, 0.5f },
				-Vec3f::Right,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 14.
				Vec3f{ -0.5f, -0.5f, 0.5f },
				-Vec3f::Right,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 15.
				Vec3f{ -0.5f, -0.5f, -0.5f },
				-Vec3f::Right,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
			},


			//Top face.
			Vertex<VertexComp::PNTanTex>{											// 16.
				Vec3f{ -0.5f, 0.5f, -0.5f },
				Vec3f::Up,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 17.
				Vec3f{ 0.5f, 0.5f, -0.5f },
				Vec3f::Up,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 18.
				Vec3f{ 0.5f, 0.5f, 0.5f },
				Vec3f::Up,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 19.
				Vec3f{ -0.5f, 0.5f, 0.5f },
				Vec3f::Up,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
			},


			// Bottom face.
			Vertex<VertexComp::PNTanTex>{											// 20.
				Vec3f{ -0.5f, -0.5f, 0.5f },
				-Vec3f::Up,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 21.
				Vec3f{ 0.5f, -0.5f, 0.5f },
				-Vec3f::Up,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 22.
				Vec3f{ 0.5f, -0.5f, -0.5f },
				-Vec3f::Up,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
			},

			Vertex<VertexComp::PNTanTex>{											// 23.
				Vec3f{ -0.5f, -0.5f, -0.5f },
				-Vec3f::Up,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
			},

		};

		constexpr uint32 totalSize = SizeOf<uint32>(vertices) * sizeof(Vertex<Comps>);
		mesh.vertices.resize(totalSize);
		MemMove(reinterpret_cast<const char*>(vertices), mesh.vertices.data(), totalSize);


		mesh.indices =
		{
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20,
		};


		if constexpr (Comps & VertexComp::Tangent)
			mesh.ComputeTangents();

		return mesh;
	}
}
