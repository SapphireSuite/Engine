// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Mesh/RawMesh.hpp>

#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
	std::shared_ptr<VertexLayout> RawMesh::GetLayout() const noexcept
	{
		return mLayout;
	}

	void RawMesh::SetLayout(VertexComp _comps)
	{
		// No conversion to perform.
		if (mLayout->comps == VertexComp::None || mLayout->comps == _comps || vertices.empty())
		{
			mLayout = VertexLayout::Make(_comps);
			return;
		}

		// TODO: Implement layout conversion.
		SA_ASSERT(Default, SA/Render, false, L"Method not implemented yet!");

		mLayout = VertexLayout::Make(_comps);
	}


	void RawMesh::Reset()
	{
		vertices.clear();
		indices.clear();
	}


	namespace Serialize
	{
		void ToBinary(const RawMesh& _obj, std::string& _str)
		{
			ToBinary(_obj.GetLayout()->comps, _str);

			ToBinary(_obj.vertices, _str);
			ToBinary(_obj.indices, _str);
		}

		void FromBinary(RawMesh& _obj, Reader& _read)
		{
			_obj.SetLayout(FromBinary<VertexComp>(_read));

			FromBinary(_obj.vertices, _read);
			FromBinary(_obj.indices, _read);
		}
	}
}