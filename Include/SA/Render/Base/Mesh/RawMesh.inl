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
			Vertex<VertexComp::PNTanTexC>{
				Vec3f{ 0.0f, 0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.5f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{
				Vec3f{ 0.5f, -0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{
				Vec3f{ -0.5f, -0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
				Vec3f::One
			},
		};

		constexpr uint32 totalSize = SizeOf(vertices) * sizeof(Vertex<Comps>);

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
			Vertex<VertexComp::PNTanTexC>{
				Vec3f{ -0.5f, 0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{
				Vec3f{ 0.5f, 0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{
				Vec3f{ 0.5f, -0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{
				Vec3f{ -0.5f, -0.5f, 0.0f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
				Vec3f::One
			},
		};

		constexpr uint32 totalSize = SizeOf(vertices) * sizeof(Vertex<Comps>);

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
			Vertex<VertexComp::PNTanTexC>{											// 0.
				Vec3f{ -0.5f, 0.5f, 0.5f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 1.
				Vec3f{ 0.5f, 0.5f, 0.5f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 2.
				Vec3f{ 0.5f, -0.5f, 0.5f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 3.
				Vec3f{ -0.5f, -0.5f, 0.5f },
				Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
				Vec3f::One
			},


			// Right face.
			Vertex<VertexComp::PNTanTexC>{											// 4.
				Vec3f{ 0.5f, 0.5f, 0.5f },
				Vec3f::Right,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 5.
				Vec3f{ 0.5f, 0.5f, -0.5f },
				Vec3f::Right,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 6.
				Vec3f{ 0.5f, -0.5f, -0.5f },
				Vec3f::Right,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 7.
				Vec3f{ 0.5f, -0.5f, 0.5f },
				Vec3f::Right,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
				Vec3f::One
			},


			// Back face.
			Vertex<VertexComp::PNTanTexC>{											// 8
				Vec3f{ 0.5f, 0.5f, -0.5f },
				-Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 9.
				Vec3f{ -0.5f, 0.5f, -0.5f },
				-Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 10.
				Vec3f{ -0.5f, -0.5f, -0.5f },
				-Vec3f::Forward,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 11.
				Vec3f{ 0.5f, -0.5f, -0.5f },
				-Vec3f::Forward,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
				Vec3f::One
			},


			// Left face.
			Vertex<VertexComp::PNTanTexC>{											// 12.
				Vec3f{ -0.5f, 0.5f, -0.5f },
				-Vec3f::Right,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 13.
				Vec3f{ -0.5f, 0.5f, 0.5f },
				-Vec3f::Right,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 14.
				Vec3f{ -0.5f, -0.5f, 0.5f },
				-Vec3f::Right,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 15.
				Vec3f{ -0.5f, -0.5f, -0.5f },
				-Vec3f::Right,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
				Vec3f::One
			},


			//Top face.
			Vertex<VertexComp::PNTanTexC>{											// 16.
				Vec3f{ -0.5f, 0.5f, -0.5f },
				Vec3f::Up,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 17.
				Vec3f{ 0.5f, 0.5f, -0.5f },
				Vec3f::Up,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 18.
				Vec3f{ 0.5f, 0.5f, 0.5f },
				Vec3f::Up,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 19.
				Vec3f{ -0.5f, 0.5f, 0.5f },
				Vec3f::Up,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
				Vec3f::One
			},


			// Bottom face.
			Vertex<VertexComp::PNTanTexC>{											// 20.
				Vec3f{ -0.5f, -0.5f, 0.5f },
				-Vec3f::Up,
				Vec3f::Zero,
				{ 0.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 21.
				Vec3f{ 0.5f, -0.5f, 0.5f },
				-Vec3f::Up,
				Vec3f::Zero,
				{ 1.0f, 0.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 22.
				Vec3f{ 0.5f, -0.5f, -0.5f },
				-Vec3f::Up,
				Vec3f::Zero,
				{ 1.0f, 1.0f },
				Vec3f::One
			},

			Vertex<VertexComp::PNTanTexC>{											// 23.
				Vec3f{ -0.5f, -0.5f, -0.5f },
				-Vec3f::Up,
				Vec3f::Zero,
				{ 0.0f, 1.0f },
				Vec3f::One
			},

		};

		constexpr uint32 totalSize = SizeOf(vertices) * sizeof(Vertex<Comps>);
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
