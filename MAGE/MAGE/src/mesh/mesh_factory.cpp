//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh_factory.hpp"
#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	UniquePtr< const StaticMesh > CreateLineCube() {

		static const VertexPosition vertices[8] = {
			VertexPosition(Point3(-0.5, -0.5, -0.5)),
			VertexPosition(Point3(-0.5, -0.5,  0.5)),
			VertexPosition(Point3(-0.5,  0.5, -0.5)),
			VertexPosition(Point3(-0.5,  0.5,  0.5)),
			VertexPosition(Point3( 0.5, -0.5, -0.5)),
			VertexPosition(Point3( 0.5, -0.5,  0.5)),
			VertexPosition(Point3( 0.5,  0.5, -0.5)),
			VertexPosition(Point3( 0.5,  0.5,  0.5))
		};

		static const U16 indices[24] = {
			0, 1,
			0, 2,
			0, 4,
			1, 3,
			1, 5,
			2, 3,
			2, 6,
			3, 7,
			4, 5,
			4, 6,
			5, 7,
			6, 7
		};

		return MakeUnique< const StaticMesh >(
								vertices, _countof(vertices), 
								indices,  _countof(indices),
								DXGI_FORMAT_R16_UINT,
								D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	}
}